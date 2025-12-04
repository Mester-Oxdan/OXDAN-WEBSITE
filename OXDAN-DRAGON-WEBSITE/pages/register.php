<?php
ini_set('session.cookie_secure', 1);
ini_set('session.cookie_httponly', 1);
ini_set('session.use_strict_mode', 1);
ini_set('session.cookie_samesite', 'Lax');

session_start();

if (empty($_SESSION['csrf_token'])) {
  $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

if (empty($_SESSION['oauth_state'])) {
  $_SESSION['oauth_state'] = bin2hex(random_bytes(16));
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Create Your Oxdan ID - Oxdan Production</title>
    <link rel="icon" href="/files/resources/images/my_dragon_ico.ico">
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600;700&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
    <script src="https://www.google.com/recaptcha/api.js?onload=onloadCallback&render=explicit" async defer></script>
    <script src="files/js/jquery.js"></script>
    <script src="files/js/minified/alert_system_script.min.js"></script>
    <script src="files/js/minified/registration_start_script.min.js"></script>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            background: #000;
            color: #f5f5f7;
            font-family: 'Inter', sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            overflow-x: hidden;
        }

        .container {
            width: 100%;
            max-width: 460px;
            padding: 40px;
            background: rgba(28, 28, 30, 0.6);
            backdrop-filter: blur(20px);
            border-radius: 18px;
            border: 1px solid rgba(255, 255, 255, 0.1);
            box-shadow: 0 20px 40px rgba(0,0,0,0.4);
            text-align: center;
        }

        h2 {
            font-size: 28px;
            font-weight: 700;
            margin-bottom: 10px;
        }

        .subtitle {
            font-size: 16px;
            color: #86868b;
            margin-bottom: 30px;
        }

        form {
            display: flex;
            flex-direction: column;
            gap: 15px;
            text-align: left;
        }

        label {
            font-size: 12px;
            font-weight: 600;
            color: #86868b;
            margin-left: 5px;
            margin-bottom: -10px;
        }

        input {
            width: 100%;
            padding: 16px;
            background: rgba(0, 0, 0, 0.2);
            border: 1px solid rgba(255, 255, 255, 0.1);
            border-radius: 12px;
            color: #fff;
            font-size: 16px;
            font-family: 'Inter', sans-serif;
            transition: border-color 0.2s, background 0.2s;
        }

        input:focus {
            outline: none;
            border-color: #0071e3;
            background: rgba(0, 0, 0, 0.4);
        }

        button[type="submit"] {
            margin-top: 10px;
            padding: 16px;
            background: #0071e3;
            color: #fff;
            border: none;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 600;
            cursor: pointer;
            transition: background 0.2s, transform 0.1s;
        }

        button[type="submit"]:hover {
            background: #0077ed;
        }

        button[type="submit"]:active {
            transform: scale(0.98);
        }

        .social-login {
            margin-top: 20px;
            padding-top: 20px;
            border-top: 1px solid rgba(255, 255, 255, 0.1);
        }

        #google-login-btn {
            width: 100%;
            padding: 12px;
            background: #fff;
            color: #333;
            border: none;
            border-radius: 12px;
            font-size: 14px;
            font-weight: 600;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }

        .links {
            margin-top: 20px;
            font-size: 14px;
            color: #86868b;
        }

        .links a {
            color: #2997ff;
            text-decoration: none;
        }

        .links a:hover {
            text-decoration: underline;
        }
        
        .captcha-wrapper {
            display: flex;
            justify-content: center;
            margin: 10px 0;
        }
    </style>
    <script>
      window.OAUTH_STATE = '<?php echo $_SESSION["oauth_state"] ?? ""; ?>';
      window.CSRF_TOKEN = '<?php echo $_SESSION["csrf_token"] ?? ""; ?>';
      window.RECAPTCHA_SITE_KEY = '6LcdQxUsAAAAAOR5GSjcIa5liqL_lX8pRXWIMrFP';
    </script>
</head>
<body>
    <div class="container">
        <h2>Create Your Oxdan ID</h2>
        <p class="subtitle">One account for everything Oxdan.</p>
        
        <form id="register_form">
            <label for="username">Username</label>
            <input type="text" id="username" placeholder="Username" maxlength="60" required>
            
            <label for="email">Email</label>
            <input type="email" id="email" placeholder="name@example.com" maxlength="60" required>
            
            <label for="password">Password</label>
            <input type="password" id="password" placeholder="Password" maxlength="60" required>
            
            <div class="captcha-wrapper">
                <div id="example2"></div>
            </div>
            
            <button type="submit">Continue</button>
        </form>
        
        <div id="response" style="margin-top: 10px;"></div>
        
        <div class="social-login">
            <button id="google-login-btn"><i class="fab fa-google"></i> Continue with Google</button>
        </div>
        
        <div class="links">
            Already have an account? <a href="/login">Sign In</a>
        </div>
    </div>
    
    <script src="https://accounts.google.com/gsi/client" async defer></script>
</body>
</html>
