<?php
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
    <title>Login - Oxdan Production</title>
    <link rel="icon" href="/files/resources/images/my_dragon_ico.ico">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
    <script src="https://www.google.com/recaptcha/api.js?onload=onloadCallback&render=explicit" async defer></script>
    
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            min-height: 100vh;
            background: #000;
            color: white;
            font-family: 'Inter', -apple-system, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
        }

        nav {
            position: fixed; top: 0; width: 100%; padding: 20px 40px;
            display: flex; justify-content: space-between; align-items: center;
            background: rgba(0,0,0,0.8); backdrop-filter: blur(20px); z-index: 100;
        }
        nav .logo { font-weight: 700; font-size: 18px; }
        nav ul { display: flex; gap: 30px; list-style: none; }
        nav a { color: white; text-decoration: none; opacity: 0.7; transition: 0.2s; }
        nav a:hover { opacity: 1; }

        .login-card {
            background: rgba(20, 20, 20, 0.8);
            backdrop-filter: blur(40px);
            border: 1px solid rgba(255, 255, 255, 0.1);
            border-radius: 24px;
            padding: 50px;
            width: 100%;
            max-width: 420px;
            margin: 100px 20px 40px;
        }

        .login-header { text-align: center; margin-bottom: 40px; }
        .login-header img { width: 60px; margin-bottom: 20px; }
        .login-header h1 { font-size: 28px; margin-bottom: 10px; }
        .login-header p { color: rgba(255,255,255,0.6); }

        .input-group { margin-bottom: 20px; }
        .input-group label { display: block; margin-bottom: 8px; color: rgba(255,255,255,0.7); font-size: 14px; }
        .input-group input {
            width: 100%;
            background: rgba(255, 255, 255, 0.05);
            border: 1px solid rgba(255, 255, 255, 0.1);
            padding: 14px 16px;
            border-radius: 12px;
            color: white;
            font-size: 16px;
            transition: all 0.2s;
        }
        .input-group input:focus {
            outline: none;
            background: rgba(255, 255, 255, 0.1);
            border-color: rgba(255, 255, 255, 0.3);
        }

        .btn-submit {
            width: 100%;
            padding: 14px;
            background: white;
            color: black;
            border: none;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 600;
            cursor: pointer;
            transition: transform 0.2s;
            margin-top: 10px;
        }
        .btn-submit:hover { transform: scale(1.02); }

        .divider {
            display: flex; align-items: center; gap: 15px;
            margin: 25px 0; color: rgba(255,255,255,0.4);
        }
        .divider::before, .divider::after {
            content: ''; flex: 1; height: 1px; background: rgba(255,255,255,0.1);
        }

        .btn-google {
            width: 100%;
            padding: 14px;
            background: transparent;
            border: 1px solid rgba(255,255,255,0.2);
            border-radius: 12px;
            color: white;
            font-size: 16px;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            transition: all 0.2s;
        }
        .btn-google:hover { background: rgba(255,255,255,0.05); }

        .links { text-align: center; margin-top: 25px; color: rgba(255,255,255,0.6); }
        .links a { color: white; text-decoration: none; }

        #response { margin-top: 15px; text-align: center; font-size: 14px; }
        .error { color: #ff4444; }
        .success { color: #44ff44; }

        .captcha-wrapper { margin: 20px 0; display: flex; justify-content: center; }
    </style>
</head>
<body>
    <nav>
        <div class="logo">OXDAN</div>
        <ul>
            <li><a href="/">Home</a></li>
            <li><a href="/faq">FAQ</a></li>
            <li><a href="/lists">Lists</a></li>
        </ul>
    </nav>

    <div class="login-card">
        <div class="login-header">
            <img src="/files/resources/images/my_dragon_ico.ico" alt="Logo">
            <h1>Welcome Back</h1>
            <p>Sign in to your account</p>
        </div>

        <form id="login-form">
            <div class="input-group">
                <label for="username">Username or Email</label>
                <input type="text" id="username" name="username" required>
            </div>
            
            <div class="input-group">
                <label for="password">Password</label>
                <input type="password" id="password" name="password" required>
            </div>

            <div class="captcha-wrapper">
                <div id="recaptcha"></div>
            </div>

            <button type="submit" class="btn-submit">Sign In</button>
        </form>

        <div id="response"></div>

        <div class="divider">or</div>

        <button id="google-login-btn" class="btn-google">
            <i class="fab fa-google"></i> Continue with Google
        </button>

        <div class="links">
            <p>Don't have an account? <a href="/register">Register</a></p>
            <p style="margin-top: 10px;"><a href="/change_password">Forgot password?</a></p>
        </div>
    </div>

    <script>
        const CSRF_TOKEN = '<?php echo $_SESSION["csrf_token"]; ?>';
        const OAUTH_STATE = '<?php echo $_SESSION["oauth_state"]; ?>';
        const RECAPTCHA_SITE_KEY = '6LcdQxUsAAAAAOR5GSjcIa5liqL_lX8pRXWIMrFP';
        let recaptchaWidgetId;

        function onloadCallback() {
            recaptchaWidgetId = grecaptcha.render('recaptcha', {
                'sitekey': RECAPTCHA_SITE_KEY,
                'theme': 'dark'
            });
        }

        document.getElementById('login-form').addEventListener('submit', async function(e) {
            e.preventDefault();
            const response = document.getElementById('response');
            const recaptchaResponse = grecaptcha.getResponse(recaptchaWidgetId);
            
            if (!recaptchaResponse) {
                response.innerHTML = '<span class="error">Please complete the reCAPTCHA</span>';
                return;
            }

            try {
                const res = await fetch('/api/login.php', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        usernameOrEmail: document.getElementById('username').value,
                        password: document.getElementById('password').value,
                        csrf_token: CSRF_TOKEN,
                        recaptcha_response: recaptchaResponse,
                        deviceInfo: {
                            userAgent: navigator.userAgent,
                            screenResolution: `${screen.width}x${screen.height}`
                        }
                    })
                });
                const data = await res.json();
                
                if (data.status === 'success') {
                    response.innerHTML = '<span class="success">Login successful! Redirecting...</span>';
                    setTimeout(() => window.location.href = '/', 1500);
                } else {
                    response.innerHTML = `<span class="error">${data.message}</span>`;
                    grecaptcha.reset(recaptchaWidgetId);
                }
            } catch (err) {
                response.innerHTML = '<span class="error">An error occurred. Please try again.</span>';
                grecaptcha.reset(recaptchaWidgetId);
            }
        });

        // Google OAuth
        document.getElementById('google-login-btn').addEventListener('click', function() {
            // Initialize Google Sign-In
            google.accounts.id.initialize({
                client_id: '<?php echo $_ENV["GOOGLE_CLIENT_ID_ACCESS_KEY"] ?? ""; ?>',
                callback: handleGoogleResponse
            });
            google.accounts.id.prompt();
        });

        async function handleGoogleResponse(response) {
            try {
                const res = await fetch('/api/oauth_google.php', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        credential: response.credential,
                        state: OAUTH_STATE
                    })
                });
                const data = await res.json();
                if (data.status === 'success') {
                    window.location.href = '/';
                } else {
                    document.getElementById('response').innerHTML = `<span class="error">${data.message}</span>`;
                }
            } catch (err) {
                document.getElementById('response').innerHTML = '<span class="error">Google login failed</span>';
            }
        }
    </script>
    <script src="https://accounts.google.com/gsi/client" async defer></script>
</body>
</html>