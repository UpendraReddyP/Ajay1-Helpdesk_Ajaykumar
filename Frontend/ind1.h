
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ATS Help Desk</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        :root {
            --primary: #4361ee;
            --secondary: #3f37c9;
            --accent: #4895ef;
            --light: #f8f9fa;
            --dark: #212529;
            --success: #4cc9f0;
            --warning: #f8961e;
            --danger: #f72585;
            --gray: #6c757d;
            --open: #4cc9f0;
            --in-progress: #f8961e;
            --resolved: #4ad66d;
            --closed: #6c757d;
        }

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        body {
            background: white;
            min-height: 100vh;
            color: var(--dark);
        }

        header {
            position: relative;
            text-align: center;
            height: 140px;
            background: linear-gradient(135deg, #6a11cb 0%, #2575fc 100%);
            color: white;
            border-radius: 15px;
            overflow: hidden;
            display: flex;
            width: 100%;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1);
            margin-bottom: 30px;
        }

        header h1 {
            margin: 0;
            font-size: 2.5rem;
            font-weight: 700;
            letter-spacing: 1px;
            position: relative;
            z-index: 2;
            text-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
        }

        header p {
            font-weight: normal;
            font-size: 1.1rem;
            margin-top: 10px;
            opacity: 0.9;
        }

        @keyframes moveCircles {
            0% { transform: translateY(0) translateX(0); }
            50% { transform: translateY(-50%) translateX(-50%); }
            100% { transform: translateY(0) translateX(0); }
        }

        .banner-background {
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            z-index: 1;
            overflow: hidden;
        }

        .circle {
            position: absolute;
            width: 200px;
            height: 200px;
            background: rgba(255, 255, 255, 0.1);
            border-radius: 50%;
            animation: moveCircles 15s infinite linear;
        }

        .circle:nth-child(1) {
            top: 10%;
            left: 20%;
            animation-duration: 15s;
        }

        .circle:nth-child(2) {
            top: 50%;
            left: 70%;
            animation-duration: 20s;
            animation-direction: reverse;
        }

        .circle:nth-child(3) {
            top: 80%;
            left: 40%;
            animation-duration: 25s;
        }

        .container {
            max-width: 1200px;
            margin: 2rem auto;
            padding: 0 1rem;
        }

        .card {
            background: white;
            border-radius: 10px;
            box-shadow: 0 8px 30px rgba(0, 0, 0, 0.1);
            padding: 2rem;
            margin-bottom: 2rem;
            transition: transform 0.3s ease, box-shadow 0.3s ease;
            animation: fadeIn 0.8s ease;
        }

        .card:hover {
            transform: translateY(-5px);
            box-shadow: 0 12px 40px rgba(0, 0, 0, 0.15);
        }

        .card h2 {
            color: var(--primary);
            margin-bottom: 1.5rem;
            display: flex;
            align-items: center;
            gap: 0.5rem;
        }

        .form-group {
            margin-bottom: 1.5rem;
        }

        .form-group label {
            display: block;
            margin-bottom: 0.5rem;
            font-weight: 600;
            color: var(--dark);
        }

        #description {
            height: 140px;
            resize: none;
        }

        .form-control {
            width: 100%;
            padding: 0.75rem;
            border: 1px solid #ddd;
            border-radius: 6px;
            font-size: 1rem;
            transition: border-color 0.3s ease, box-shadow 0.3s ease;
        }

        .form-control:focus {
            outline: none;
            border-color: var(--accent);
            box-shadow: 0 0 0 3px rgba(67, 97, 238, 0.2);
        }

        .invalid-feedback {
            color: var(--danger);
            font-size: 0.85rem;
            margin-top: 0.25rem;
            display: none;
        }

        .btn {
            display: inline-flex;
            align-items: center;
            justify-content: center;
            gap: 0.5rem;
            padding: 0.75rem 1.5rem;
            border: none;
            border-radius: 6px;
            font-size: 1rem;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.3s ease;
            text-decoration: none;
        }

        .btn-primary {
            background: var(--primary);
            color: white;
        }

        .btn-primary:hover {
            background: var(--secondary);
            transform: translateY(-2px);
        }

        .btn-primary:active {
            transform: translateY(0);
        }

        .ticket-preview {
            margin-top: 2rem;
            padding: 1.5rem;
            background: rgba(67, 97, 238, 0.05);
            border-left: 4px solid var(--primary);
            border-radius: 0 6px 6px 0;
            display: none;
        }

        .ticket-preview h3 {
            margin-bottom: 1rem;
            color: var(--primary);
        }

        .ticket-preview p {
            margin-bottom: 0.5rem;
        }

        .ticket-preview strong {
            color: var(--dark);
        }

        .tickets-table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 1rem;
        }

        .tickets-table th, .tickets-table td {
            padding: 1rem;
            text-align: left;
            border-bottom: 1px solid #eee;
        }

        .tickets-table th {
            background: rgba(67, 97, 238, 0.05);
            font-weight: 600;
            color: var(--primary);
        }

        .tickets-table tr:hover {
            background: rgba(67, 97, 238, 0.03);
        }

        .status-badge {
            display: inline-block;
            padding: 0.25rem 0.75rem;
            border-radius: 20px;
            font-size: 0.8rem;
            font-weight: 600;
        }

        .status-open {
            background: rgba(76, 201, 240, 0.1);
            color: var(--open);
        }

        .status-in-progress {
            background: rgba(248, 150, 30, 0.1);
            color: var(--in-progress);
        }

        .status-resolved {
            background: rgba(74, 214, 109, 0.1);
            color: var(--resolved);
        }

        .status-closed {
            background: rgba(108, 117, 125, 0.1);
            color: var(--closed);
        }

        .priority-high {
            color: var(--danger);
            font-weight: 600;
        }

        .priority-critical {
            color: var(--danger);
            font-weight: 600;
            animation: pulse 1.5s infinite;
        }

        .action-btn {
            background: none;
            border: none;
            cursor: pointer;
            font-size: 1rem;
            margin: 0 0.25rem;
            transition: transform 0.2s ease;
        }

        .action-btn:hover {
            transform: scale(1.2);
        }

        .btn-view {
            color: var(--accent);
        }

        .filters {
            display: flex;
            flex-wrap: wrap;
            gap: 1rem;
            margin-bottom: 1.5rem;
        }

        .filter-group {
            flex: 1;
            min-width: 200px;
        }

        .filter-group label {
            display: block;
            margin-bottom: 0.5rem;
            font-weight: 600;
            color: var(--dark);
        }

        .filter-control {
            width: 100%;
            padding: 0.5rem 1rem;
            border: 1px solid #ddd;
            border-radius: 6px;
            font-size: 1rem;
        }

        .modal {
            position: fixed;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: rgba(0, 0, 0, 0.5);
            display: flex;
            align-items: center;
            justify-content: center;
            z-index: 1000;
            opacity: 0;
            visibility: hidden;
            transition: all 0.3s ease;
        }

        .modal.active {
            opacity: 1;
            visibility: visible;
        }

        .modal-content {
            background: white;
            border-radius: 10px;
            width: 90%;
            max-width: 500px;
            padding: 2rem;
            transform: translateY(-20px);
            transition: all 0.3s ease;
            text-align: center;
        }

        .modal.active .modal-content {
            transform: translateY(0);
        }

        .modal-icon {
            font-size: 4rem;
            margin-bottom: 1.5rem;
            color: var(--success);
        }

        .modal h3 {
            margin-bottom: 1rem;
            font-size: 1.5rem;
        }

        .modal p {
            margin-bottom: 2rem;
            color: var(--gray);
        }

        .modal-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 1rem;
            padding-bottom: 1rem;
            border-bottom: 1px solid #eee;
        }

        .modal-close {
            background: none;
            border: none;
            font-size: 1.5rem;
            cursor: pointer;
            color: var(--gray);
        }

        .ticket-details p {
            margin-bottom: 0.75rem;
        }

        .ticket-details strong {
            min-width: 120px;
            display: inline-block;
            color: var(--dark);
        }

        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }

        @keyframes slideInDown {
            from {
                transform: translateY(-50px);
                opacity: 0;
            }
            to {
                transform: translateY(0);
                opacity: 1;
            }
        }

        @keyframes slideInUp {
            from {
                transform: translateY(50px);
                opacity: 0;
            }
            to {
                transform: translateY(0);
                opacity: 1;
            }
        }

        @keyframes bounce {
            0%, 20%, 50%, 80%, 100% {
                transform: translateY(0);
            }
            40% {
                transform: translateY(-20px);
            }
            60% {
                transform: translateY(-10px);
            }
        }

        @keyframes pulse {
            0% { opacity: 1; }
            50% { opacity: 0.6; }
            100% { opacity: 1; }
        }

        .bounce {
            animation: bounce 1s;
        }

        @media (max-width: 768px) {
            header h1 {
                font-size: 2rem;
            }

            .card {
                padding: 1.5rem;
            }

            .tickets-table {
                display: block;
                overflow-x: auto;
            }

            .filters {
                flex-direction: column;
                gap: 1rem;
            }

            .filter-group {
                min-width: 100%;
            }
        }
    </style>
</head>
<body>
    <header>
        <div class="banner-background">
            <div class="circle"></div>
            <div class="circle"></div>
            <div class="circle"></div>
        </div>
        <h1><i class="fas fa-headset"></i> ATS Help Desk</h1>
        <p>Submit your queries and issues here. Our team will get back to you shortly.</p>
    </header>

    <div class="container">
        <div class="card">
            <h2><i class="fas fa-ticket-alt"></i> Create New Ticket</h2>
            <form id="ticketForm" novalidate>
                <div class="form-group">
                    <label for="empId">Employee ID</label>
                    <input type="text" id="empId" class="form-control" placeholder="ATS0xxx" pattern="^ATS0[0-9]{3}$" minlength="7" maxlength="7" required>
                    <div class="invalid-feedback">Please enter a valid Employee ID (ATS0 followed by 3 digits, not all zeros)</div>
                </div>
                <div class="form-group">
                    <label for="empName">Full Name</label>
                    <input type="text" id="empName" class="form-control" placeholder="Employee Name" pattern="^[A-Za-z]+$" title="Only alphabets, no spaces or special characters" required minlength="3" maxlength="100">
                    <div class="invalid-feedback">Please enter a valid name (only alphabets, max 100 chars)</div>
                </div>
                <div class="form-group">
                    <label for="empEmail">Email Address</label>
<input type="email" id="empEmail" class="form-control" placeholder="Employee Email"
       pattern="[a-zA-Z0-9._%+-]+@(gmail\.com|outlook\.com|[a-zA-Z0-9-]+\.in|[a-zA-Z0-9-]+\.org\.co)"
       required minlength="3" maxlength="100">
                    <div class="invalid-feedback">Please enter a valid email (gmail.com, outlook.com, .in, or .org.co domains)</div>
                </div>
                <div class="form-group">
                    <label for="department">Department</label>
                    <select id="department" class="form-control" required>
                        <option value="">Select Department</option>
                        <option value="IT">IT</option>
                        <option value="HR">Human Resources</option>
                        <option value="Finance">Finance</option>
                        <option value="Operations">Operations</option>
                        <option value="Marketing">Marketing</option>
                        <option value="Other">Other</option>
                    </select>
                    <div class="invalid-feedback">Please select a department</div>
                </div>
                <div class="form-group">
                    <label for="priority">Priority</label>
                    <select id="priority" class="form-control" required>
                        <option value="">Select Priority</option>
                        <option value="Low">Low</option>
                        <option value="Medium">Medium</option>
                        <option value="High">High</option>
                        <option value="Critical">Critical</option>
                    </select>
                    <div class="invalid-feedback">Please select a priority level</div>
                </div>
                <div class="form-group">
                    <label for="issueType">Issue Type</label>
                    <select id="issueType" class="form-control" required>
                        <option value="">Select Issue Type</option>
                        <option value="Technical">Technical Issue</option>
                        <option value="Hardware">Hardware Problem</option>
                        <option value="Software">Software Problem</option>
                        <option value="Access">Access Request</option>
                        <option value="Account">Account Issue</option>
                        <option value="Other">Other</option>
                    </select>
                    <div class="invalid-feedback">Please select an issue type</div>
                </div>
                <div class="form-group">
                    <label for="description">Description</label>
                    <textarea id="description" class="form-control" rows="5" placeholder="Describe your issue in detail..." minlength="5" maxlength="500" title="Minimum 5 characters with letters" required></textarea>
                    <div class="invalid-feedback">Please provide a valid description (min 5 chars with letters, max 500 chars)</div>
                </div>
                <button type="submit" class="btn btn-primary"><i class="fas fa-paper-plane"></i> Submit Ticket</button>
            </form>
            <div class="ticket-preview" id="ticketDetails">
                <h3><i class="fas fa-ticket"></i> Ticket Details</h3>
                <p><strong>Ticket ID:</strong> <span id="previewTicketId"></span></p>
                <p><strong>Employee ID:</strong> <span id="previewEmpId"></span></p>
                <p><strong>Name:</strong> <span id="previewEmpName"></span></p>
                <p><strong>Department:</strong> <span id="previewDepartment"></span></p>
                <p><strong>Priority:</strong> <span id="previewPriority"></span></p>
                <p><strong>Issue Type:</strong> <span id="previewIssueType"></span></p>
                <p><strong>Description:</strong> <span id="previewDescription"></span></p>
            </div>
        </div>

        <div class="card" id="myTicketsCard" style="display: none;">
            <h2><i class="fas fa-ticket-alt"></i> My Tickets</h2>
            <div class="filters">
                <div class="filter-group">
                    <label for="filterStatusEmp">Status</label>
                    <select id="filterStatusEmp" class="filter-control">
                        <option value="">All Statuses</option>
                        <option value="Open">Open</option>
                        <option value="In Progress">In Progress</option>
                        <option value="Resolved">Resolved</option>
                        <option value="Closed">Closed</option>
                    </select>
                </div>
            </div>
            <table class="tickets-table">
                <thead>
                    <tr>
                        <th>Ticket ID</th>
                        <th>Department</th>
                        <th>Issue Type</th>
                        <th>Priority</th>
                        <th>Status</th>
                        <th>Created</th>
                        <th>Actions</th>
                    </tr>
                </thead>
                <tbody id="myTicketsBody">
                    <!-- tickets will be loaded here -->
                </tbody>
            </table>
        </div>
    </div>

    <div id="successModal" class="modal">
        <div class="modal-content">
            <div class="modal-icon"><i class="fas fa-check-circle bounce"></i></div>
            <h3>Ticket Submitted Successfully!</h3>
            <p>Your ticket has been created and assigned a reference number. Our team will get back to you soon.</p>
            <button class="btn btn-primary" onclick="closeModal()"><i class="fas fa-thumbs-up"></i> Got it!</button>
        </div>
    </div>

    <div id="ticketModal" class="modal">
        <div class="modal-content" style="max-width: 700px; text-align: left;">
            <div class="modal-header">
                <h3><i class="fas fa-ticket-alt"></i> <span id="modalTicketId"></span></h3>
                <button class="modal-close" onclick="closeTicketModal()">×</button>
            </div>
            <div class="ticket-details">
                <p><strong>Status:</strong> <span id="modalStatus"></span></p>
                <p><strong>Priority:</strong> <span id="modalPriority"></span></p>
                <p><strong>Department:</strong> <span id="modalDepartment"></span></p>
                <p><strong>Issue Type:</strong> <span id="modalIssueType"></span></p>
                <p><strong>Created:</strong> <span id="modalCreated"></span></p>
                <p><strong>Description:</strong></p>
                <div style="background: #f8f9fa; padding: 1rem; border-radius: 6px; margin-top: 0.5rem;">
                    <span id="modalDescription"></span>
                </div>
            </div>
            <div style="margin-top: 2rem;">
                <h3><i class="fas fa-ticket"></i> Comments</h3>
                <div id="commentsHistory" style="margin-top: 1rem;">
                    <!-- Comments will be loaded here -->
                </div>
            </div>
        </div>
    </div>

    <script>
        console.log('index.html loaded, version: 2025-10-28-final-v7');
        let currentTicketId = null;
        let currentEmpId = null;
        const API_BASE_URL = 'http://51.20.55.179:3088';

        // Check if response is JSON
        async function checkResponse(response) {
            const contentType = response.headers.get('content-type') || '';
            if (!contentType.includes('application/json')) {
                const text = await response.text();
                console.error('Unexpected response type:', contentType, 'Body:', text.slice(0, 100));
                throw new Error(`Unexpected response: ${text.includes('<!DOCTYPE html>') ? 'Received HTML instead of JSON' : contentType}`);
            }
            return response.json();
        }

        function validateEmpName(name) {
            if (name !== name.trim()) {
                console.log('empName validation failed: Leading/trailing spaces');
                return false;
            }
            if (name.includes('  ')) {
                console.log('Invalid empName validation failed: Double spaces');
                return false;
            }
            if (name.length > 100 || name.length < 3) {
                console.log('Invalid empName validation failed: Length < 3 or > 100');
                return false;
            }
            if (!/^[A-Za-z]+$/.test(name)) {
                console.log('Invalid empName validation failed: Invalid characters');
                return false;
            }
            return true;
        }

        function validateDescription(description) {
            if (description !== description.trim()) {
                console.log('Description validation failed: Leading/trailing spaces');
                return false;
            }
            if (description.includes('  ')) {
                console.log('Description validation failed: Double spaces');
                return false;
            }
            if (description.length < 5 || description.length > 500) {
                console.log('Description validation failed: Length < 5 or > 500');
                return false;
            }
            if (!/[a-zA-Z]/.test(description)) {
                console.log('Description validation failed: No letters');
                return false;
            }
            if (/^\d+$/.test(description.replace(/\s/g, ''))) {
                console.log('Description validation failed: Only numbers');
                return false;
            }
            return true;
        }

        function validateField(field) {
            const feedback = field.nextElementSibling;
            let isValid = true;

            if (field.id === 'empId') {
                if (!/^ATS0[0-9]{3}$/.test(field.value) || field.value === 'ATS0000') {
                    console.log('empId validation failed:', field.value);
                    isValid = false;
                }
            } else if (field.id === 'empName') {
                if (!validateEmpName(field.value)) {
                    console.log('empName validation failed:', field.value);
                    isValid = false;
                }
            } else if (field.id === 'empEmail') {
const emailRegex = /^[a-zA-Z0-9._%+-]+@(gmail\.com|outlook\.com|[a-zA-Z0-9-]+\.in|[a-zA-Z0-9-]+\.org\.co)$/;                if (!emailRegex.test(field.value) || field.value.length > 100) {
                    console.log('empEmail validation failed:', field.value);
                    isValid = false;
                }
            } else if (field.id === 'department' || field.id === 'priority' || field.id === 'issueType') {
                if (!field.value) {
                    console.log(`${field.id} validation failed:`, field.value);
                    isValid = false;
                }
            } else if (field.id === 'description') {
                if (!validateDescription(field.value)) {
                    console.log('Description validation failed:', field.value);
                    isValid = false;
                }
            } else {
                try {
                    if (!field.checkValidity()) {
                        console.log(`${field.id} HTML5 validation failed:`, field.value);
                        isValid = false;
                    }
                } catch (err) {
                    console.error('HTML5 validation error:', err.message);
                    isValid = false;
                }
            }

            field.classList.toggle('is-invalid', !isValid);
            feedback.style.display = isValid ? 'none' : 'block';
            return isValid;
        }

        document.addEventListener('DOMContentLoaded', () => {
            console.log('DOM loaded, initializing form validation');
            const formControls = document.querySelectorAll('.form-control');
            formControls.forEach(control => {
                const eventType = control.tagName === 'SELECT' ? 'change' : 'input';
                control.addEventListener(eventType, () => validateField(control));
            });
        });

        document.getElementById('ticketForm').addEventListener('submit', async (e) => {
            e.preventDefault();

            let isValid = true;
            const formControls = document.querySelectorAll('.form-control');

            formControls.forEach(control => {
                if (!validateField(control)) {
                    isValid = false;
                }
            });

            if (!isValid) {
                console.log('Form validation failed');
                return;
            }

            try {
                const ticketData = {
                    emp_id: document.getElementById('empId').value.trim(),
                    emp_name: document.getElementById('empName').value.trim(),
                    emp_email: document.getElementById('empEmail').value.trim(),
                    department: document.getElementById('department').value,
                    priority: document.getElementById('priority').value,
                    issue_type: document.getElementById('issueType').value,
                    description: document.getElementById('description').value.trim()
                };
                console.log('Submitting ticket data:', ticketData);

                const response = await fetch(`${API_BASE_URL}/api/tickets`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(ticketData)
                });

                const ticket = await checkResponse(response);

                document.getElementById('previewTicketId').textContent = ticket.ticket_id;
                document.getElementById('previewEmpId').textContent = ticket.emp_id;
                document.getElementById('previewEmpName').textContent = ticket.emp_name;
                document.getElementById('previewDepartment').textContent = ticket.department;
                document.getElementById('previewPriority').textContent = ticket.priority;
                document.getElementById('previewIssueType').textContent = ticket.issue_type;
                document.getElementById('previewDescription').textContent = ticket.description;

                document.getElementById('ticketDetails').style.display = 'block';
                document.getElementById('successModal').classList.add('active');

                if (currentEmpId === ticket.emp_id) {
                    await loadMyTickets();
                }

                document.getElementById('ticketForm').reset();
                formControls.forEach(control => {
                    control.classList.remove('is-invalid');
                    control.nextElementSibling.style.display = 'none';
                });
            } catch (error) {
                console.error('Error submitting ticket:', error);
                alert(`Error submitting ticket: ${error.message}. Please ensure the server is running at ${API_BASE_URL}.`);
            }
        });

        document.getElementById('empId').addEventListener('change', async () => {
            currentEmpId = document.getElementById('empId').value.trim();
            if (/^ATS0[0-9]{3}$/.test(currentEmpId) && currentEmpId !== 'ATS0000') {
                document.getElementById('myTicketsCard').style.display = 'block';
                await loadMyTickets();
            } else {
                document.getElementById('myTicketsCard').style.display = 'none';
            }
        });

        document.getElementById('filterStatusEmp').addEventListener('change', loadMyTickets);

        async function loadMyTickets() {
            if (!currentEmpId) {
                console.log('No employee ID provided');
                return;
            }

            try {
                const statusFilter = document.getElementById('filterStatusEmp').value;
                const params = new URLSearchParams();
                params.append('emp_id', currentEmpId);
                if (statusFilter) params.append('status', statusFilter);

                console.log('Fetching tickets from:', `${API_BASE_URL}/api/tickets?${params.toString()}`);

                const response = await fetch(`${API_BASE_URL}/api/tickets?${params.toString()}`, {
                    method: 'GET',
                    headers: { 'Content-Type': 'application/json' }
                });

                const tickets = await checkResponse(response);
                console.log('Tickets received:', tickets);

                const ticketsBody = document.getElementById('myTicketsBody');
                ticketsBody.innerHTML = '';

                if (tickets.length === 0) {
                    ticketsBody.innerHTML = '<tr><td colspan="7" style="text-align: center; padding: 2rem;">No tickets found</td></tr>';
                    return;
                }

                tickets.forEach(ticket => {
                    const row = document.createElement('tr');
                    const createdDate = new Date(ticket.created_at);
                    const formattedDate = createdDate.toLocaleDateString() + ' ' + createdDate.toLocaleTimeString();

                    const priorityClass = ticket.priority === 'High' ? 'priority-high' : ticket.priority === 'Critical' ? 'priority-critical' : '';
                    const statusBadge = ticket.status === 'Open' ? 'status-open' :
                        ticket.status === 'In Progress' ? 'status-in-progress' :
                        ticket.status === 'Resolved' ? 'status-resolved' : 'status-closed';

                    row.innerHTML = `
                        <td>${ticket.ticket_id}</td>
                        <td>${ticket.department}</td>
                        <td>${ticket.issue_type}</td>
                        <td class="${priorityClass}">${ticket.priority}</td>
                        <td><span class="status-badge ${statusBadge}">${ticket.status}</span></td>
                        <td>${formattedDate}</td>
                        <td>
                            <button class="action-btn btn-view" onclick="viewTicket('${ticket.ticket_id}')" title="View Ticket">
                                <i class="fas fa-eye"></i>
                            </button>
                        </td>
                    `;
                    ticketsBody.appendChild(row);
                });
            } catch (error) {
                console.error('Error fetching tickets:', error);
                const ticketsBody = document.getElementById('myTicketsBody');
                ticketsBody.innerHTML = `<tr><td colspan="7" style="text-align: center; padding: 2rem;">Error: ${error.message}. Please ensure the server is running at ${API_BASE_URL}.</td></tr>`;
                alert(`Error fetching tickets: ${error.message}. Please ensure the server is running at ${API_BASE_URL}.`);
            }
        }

        async function viewTicket(ticketId) {
            try {
                console.log('Viewing ticket:', ticketId);
                const response = await fetch(`${API_BASE_URL}/api/tickets/${ticketId}`);
                const ticket = await checkResponse(response);
                currentTicketId = ticket.ticket_id;

                const createdDate = new Date(ticket.created_at);
                const formattedDate = createdDate.toLocaleDateString() + ' ' + createdDate.toLocaleTimeString();

                document.getElementById('modalTicketId').textContent = ticket.ticket_id;
                document.getElementById('modalStatus').textContent = ticket.status;
                document.getElementById('modalPriority').textContent = ticket.priority;
                document.getElementById('modalDepartment').textContent = ticket.department;
                document.getElementById('modalIssueType').textContent = ticket.issue_type;
                document.getElementById('modalCreated').textContent = formattedDate;
                document.getElementById('modalDescription').textContent = ticket.description;

                await loadComments();
                document.getElementById('ticketModal').classList.add('active');
            } catch (error) {
                console.error('Error viewing ticket:', error);
                alert(`Error viewing ticket details: ${error.message}. Please ensure the server is running at ${API_BASE_URL}.`);
            }
        }

        async function loadComments() {
            if (!currentTicketId) {
                console.log('No ticket ID selected for comments');
                return;
            }

            try {
                console.log('Loading comments for ticket:', currentTicketId);
                const response = await fetch(`${API_BASE_URL}/api/tickets/${currentTicketId}/comments`);
                const comments = await checkResponse(response);

                const commentsBody = document.getElementById('commentsBody');
                commentsBody.innerHTML = '';

                if (comments.length === 0) {
                    commentsBody.innerHTML = '<p>No comments available</p>';
                    return;
                }

                comments.forEach(comment => {
                    const commentDiv = document.createElement('div');
                    const commentDate = new Date(comment.created_at);
                    const formattedDate = commentDate.toLocaleDateString() + ' ' + commentDate.toLocaleTimeString();

                    commentDiv.style.padding = '10px';
                    commentDiv.style.borderBottom = '1px solid #eee';
                    commentDiv.innerHTML = `
                        <p><strong>${comment.author}</strong> <small>${formattedDate}</small></p>
                        <p>${comment.comment}</p>
                    `;
                    commentsBody.appendChild(commentDiv);
                });
            } catch (error) {
                console.error('Error fetching comments:', error);
                const commentsBody = document.getElementById('CommentsBody');
                commentsBody.innerHTML = `<p>Error fetching comments: ${error.message}</p>`;
            }
        }

        function closeModal() {
            document.getElementById('successModal').classList.remove('active');
        }

        function closeTicketModal() {
            document.getElementById('ticketModal').classList.remove('active');
            currentTicketId = null;
        }
    </script>
</body>
</html>
