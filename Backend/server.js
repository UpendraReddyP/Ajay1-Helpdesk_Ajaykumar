require('dotenv').config();
const express = require('express');
const cors = require('cors');
const { Pool } = require('pg');

const app = express();
const port = process.env.PORT || 3426;

// PostgreSQL connection with retry logic
const createPool = () => {
  return new Pool({
    user: process.env.DB_USER || 'postgres',
    host: process.env.DB_HOST || 'postgres',
    database: process.env.DB_NAME || 'new_employee_db',
    password: process.env.DB_PASSWORD || 'admin123',
    port: process.env.DB_PORT || 5432,
  });
};

let pool = createPool();

// Middleware
app.use(cors({
    origin: [
        'http://51.20.55.179:8145',
        'http://51.20.55.179:8146',
        'http://127.0.0.1:3025',
        'http://127.0.0.1:5500',
        'http://localhost:8145'
    ],
    methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
    allowedHeaders: ['Content-Type', 'Authorization']
}));
app.use(express.json());

// Database initialization with retry
const createTables = async () => {
  await pool.query(`
    CREATE TABLE IF NOT EXISTS tickets (
      id SERIAL PRIMARY KEY,
      ticket_id VARCHAR(20) UNIQUE NOT NULL,
      emp_id VARCHAR(10) NOT NULL,
      emp_name VARCHAR(100) NOT NULL,
      emp_email VARCHAR(100) NOT NULL,
      department VARCHAR(50) NOT NULL,
      priority VARCHAR(20) NOT NULL,
      issue_type VARCHAR(50) NOT NULL,
      description TEXT NOT NULL,
      status VARCHAR(20) DEFAULT 'Open',
      created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
      updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );
  `);

  await pool.query(`
    CREATE TABLE IF NOT EXISTS comments (
      id SERIAL PRIMARY KEY,
      ticket_id VARCHAR(20) REFERENCES tickets(ticket_id) ON DELETE CASCADE,
      comment TEXT NOT NULL,
      author VARCHAR(100) NOT NULL,
      created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );
  `);
};

const initializeDatabase = async () => {
  let retries = 5;
  while (retries) {
    try {
      await pool.query('SELECT 1');
      await createTables();
      console.log('Database connected and tables initialized');
      return;
    } catch (err) {
      retries--;
      console.log(`Database connection failed, retries left: ${retries}`, err.message);
      await new Promise(res => setTimeout(res, 5000));
      
      if (pool) await pool.end();
      pool = createPool();
    }
  }
  throw new Error('Failed to connect to database after retries');
};

// Health check endpoint
app.get('/api/health', (req, res) => {
  res.status(200).json({ status: 'healthy', timestamp: new Date() });
});

// Create new ticket
app.post('/api/tickets', async (req, res) => {
    try {
        const { emp_id, emp_name, emp_email, department, priority, issue_type, description } = req.body;

        if (!/^ATS0[0-9]{3}$/.test(emp_id) || emp_id === 'ATS0000') {
            return res.status(400).json({ error: 'Invalid Employee ID format' });
        }

        if (!/@(gmail\.com|outlook\.com|[\w-]+\.in|[\w-]+\.org\.co)$/.test(emp_email)) {
            return res.status(400).json({ error: 'Invalid email domain' });
        }

        const ticket_id = 'TKT-' + Math.floor(100000 + Math.random() * 900000);

        const result = await pool.query(
            'INSERT INTO tickets (ticket_id, emp_id, emp_name, emp_email, department, priority, issue_type, description) VALUES ($1, $2, $3, $4, $5, $6, $7, $8) RETURNING *',
            [ticket_id, emp_id, emp_name, emp_email, department, priority, issue_type, description]
        );

        res.status(201).json(result.rows[0]);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Get all tickets with optional filters
app.get('/api/tickets', async (req, res) => {
    try {
        const { emp_id, status, priority, department, issue_type } = req.query;

        let query = 'SELECT * FROM tickets';
        const params = [];
        const conditions = [];

        if (emp_id) {
            params.push(emp_id);
            conditions.push(`emp_id = $${params.length}`);
        }
        if (status) {
            params.push(status);
            conditions.push(`status = $${params.length}`);
        }
        if (priority) {
            params.push(priority);
            conditions.push(`priority = $${params.length}`);
        }
        if (department) {
            params.push(department);
            conditions.push(`department = $${params.length}`);
        }
        if (issue_type) {
            params.push(issue_type);
            conditions.push(`issue_type = $${params.length}`);
        }

        if (conditions.length > 0) {
            query += ' WHERE ' + conditions.join(' AND ');
        }

        query += ' ORDER BY created_at DESC';

        const result = await pool.query(query, params);
        res.json(result.rows);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Get single ticket by ID
app.get('/api/tickets/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await pool.query('SELECT * FROM tickets WHERE ticket_id = $1', [id]);

        if (result.rows.length === 0) {
            return res.status(404).json({ error: 'Ticket not found' });
        }

        res.json(result.rows[0]);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Update ticket status
app.put('/api/tickets/:id/status', async (req, res) => {
    try {
        const { id } = req.params;
        const { status } = req.body;

        if (!['Open', 'In Progress', 'Resolved', 'Closed'].includes(status)) {
            return res.status(400).json({ error: 'Invalid status' });
        }

        const result = await pool.query(
            'UPDATE tickets SET status = $1, updated_at = CURRENT_TIMESTAMP WHERE ticket_id = $2 RETURNING *',
            [status, id]
        );

        if (result.rows.length === 0) {
            return res.status(404).json({ error: 'Ticket not found' });
        }

        res.json(result.rows[0]);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Add comment to ticket
app.post('/api/tickets/:id/comments', async (req, res) => {
    try {
        const { id } = req.params;
        const { comment, author } = req.body;

        const ticketCheck = await pool.query('SELECT 1 FROM tickets WHERE ticket_id = $1', [id]);
        if (ticketCheck.rows.length === 0) {
            return res.status(404).json({ error: 'Ticket not found' });
        }

        const result = await pool.query(
            'INSERT INTO comments (ticket_id, comment, author) VALUES ($1, $2, $3) RETURNING *',
            [id, comment, author]
        );

        res.status(201).json(result.rows[0]);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Get all comments for a ticket
app.get('/api/tickets/:id/comments', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await pool.query(
            'SELECT * FROM comments WHERE ticket_id = $1 ORDER BY created_at ASC',
            [id]
        );

        res.json(result.rows);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Get ticket statistics
app.get('/api/tickets/stats', async (req, res) => {
    try {
        const result = await pool.query(`
            SELECT
                status,
                COUNT(*) as count
            FROM tickets
            GROUP BY status
        `);

        const stats = {
            Open: 0,
            'In Progress': 0,
            Resolved: 0,
            Closed: 0
        };

        result.rows.forEach(row => {
            stats[row.status] = parseInt(row.count);
        });

        res.json(stats);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({ error: 'Something went wrong!' });
});

// Start server
const startServer = async () => {
    try {
        await initializeDatabase();
        app.listen(port, '0.0.0.0', () => {
            console.log(`Server running on port ${port}`);
        });
    } catch (err) {
        console.error('Failed to start server:', err);
        process.exit(1);
    }
};

// Graceful shutdown
process.on('SIGTERM', async () => {
    console.log('SIGTERM received. Shutting down gracefully...');
    await pool.end();
    process.exit(0);
});

process.on('SIGINT', async () => {
    console.log('SIGINT received. Shutting down gracefully...');
    await pool.end();
    process.exit(0);
});

startServer();