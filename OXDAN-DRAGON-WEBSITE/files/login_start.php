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
    <meta name="description" content="Log in to your Oxdan Praduction account today! Stay secure, manage your settings, and explore personalized features — fast, safe, and easy.">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LOGIN</title>
    <link id="logo-icon" rel="icon" type="image/png" href="files/resources/images/my_dragon_ico.ico">
    <script src="files/js/jquery.js"></script>
    <script src="files/js/minified/alert_system_script.min.js"></script>
    <script src="https://www.google.com/recaptcha/api.js?onload=onloadCallback&render=explicit" async defer></script>
    <script src="files/js/minified/login_start_script.min.js"></script>
    <link rel="stylesheet" type="text/css" href="files/css/minified/login_style.min.css">
    <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.0.3/css/font-awesome.min.css">
    <script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-2281387454588748" crossorigin="anonymous"></script>
    <script>
      window.OAUTH_STATE = '<?php echo $_SESSION["oauth_state"] ?? ""; ?>';
      window.CSRF_TOKEN = '<?php echo $_SESSION["csrf_token"] ?? ""; ?>';
      window.RECAPTCHA_SITE_KEY = '6LcdQxUsAAAAAOR5GSjcIa5liqL_lX8pRXWIMrFP';
      document.addEventListener("DOMContentLoaded", function () {
        function getSeason(date) {
          const month = date.getMonth();

          if (month === 0 || month === 1 || month === 11) {
            return "winter";
          }
          return "other";
        }
  
        function setFavicon(path) {
          const old = document.getElementById("logo-icon");
          if (old) {
            old.remove();
          }
  
          const link = document.createElement("link");
          link.id = "logo-icon";
          link.rel = "icon";
          link.type = "image/x-icon";
          link.href = path + "?v=" + Date.now();
          document.head.appendChild(link);
        }
  
        const currentSeason = getSeason(new Date());
        if (currentSeason === "winter") {
          setFavicon("files/resources/images/my_dragon_winter_ico.ico");
        } else {
          setFavicon("files/resources/images/my_dragon_ico.ico");
        }
      });
    </script>
  </head>
  <body>
    <div class="container">
      <h2>Login</h2>
      <form id="login-form">
        <label for="username">Username or Email:</label>
        <input type="text" id="username" name="username" maxlength="60" required>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" maxlength="60" required>
        <label for="showPassword" id="showPasswordLabel" class="show-password"></label><br>
        <div class="captcha-wrapper">
          <div id="example1"></div>
        </div>
        <button type="submit" style="font-family: Arial, sans-serif;">Login</button>
      </form>
      <div id="response"></div>
      <br>
      <div class="social-login">
      <button id="google-login-btn">Login with Google</button>
    </div>
    <script src="https://accounts.google.com/gsi/client" async defer></script>
    </div>
  </body>
</html>