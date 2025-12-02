<?php 

include 'php/auth.php'; 
$allowedMethods = ['normal'];

if (!isset($_SESSION['verified_password_reset'])) {
  $currentMethod = $_SESSION['login_method'] ?? 'unknown';
  
  if (!in_array($currentMethod, $allowedMethods)) {
    header('Location: /skip_login?not_allowed_password_change=1');
    exit;
  }
}
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CHANGE PASSWORD</title>
    <link id="logo-icon" rel="icon" type="image/png" href="files/resources/images/my_dragon_ico.ico">
    <link rel="stylesheet" type="text/css" href="files/css/minified/change_password_style.min.css">
    <script src="https://www.google.com/recaptcha/api.js?onload=onloadCallback&render=explicit" async defer></script>
    <script src="files/js/jquery.js"></script>
    <script src="files/js/minified/alert_system_script.min.js"></script>
    <script src="files/js/minified/change_password_start_script.min.js?v=647284529"></script>
    <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.0.3/css/font-awesome.min.css">
    <script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-2281387454588748" crossorigin="anonymous"></script>
    <script>
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
      <h2>CHANGE PASSWORD</h2>
      <form id="changePasswordForm">
        <label for="current_password">Current Password:</label>
        <input type="password" id="current_password" maxlength="60" required>
        <label for="password">New Password:</label>
        <input type="password" id="password" maxlength="60" required>
        <label for="showPassword" id="showPasswordLabel" class="show-password"></label><br>
        <div id="example3"></div>
        <button type="submit">Submit</button>
      </form>
      <div id="response"></div>
      <script type="text/javascript">
        var verifyCallback = function(response) {
          alert(response);
        };
        var widgetId1;
        var onloadCallback = function() {
          widgetId1 = grecaptcha.render('example3', {
            'sitekey' : window.RECAPTCHA_SITE_KEY,
            'theme' : 'light'
          });
        };
        
        $(document).ready(function() {
          $('#changePasswordForm').submit(function(event) {
            if (confirm("Are you sure you want to change your password?")) {
              change_password(event);
            } else {
              event.preventDefault();
            }
          });

          $('#showPasswordLabel').on('click', function() {
            var currentPasswordInput = $('#current_password');
            var newPasswordInput = $('#password');
            var showpassword_css = $('#showPasswordLabel');

            if (currentPasswordInput.attr('type') === 'password') {
              currentPasswordInput.attr('type', 'text');
              newPasswordInput.attr('type', 'text');
              showpassword_css.css('background-image', "url('files/resources/images/open_eye.png')");
            } else {
              currentPasswordInput.attr('type', 'password');
              newPasswordInput.attr('type', 'password');
              showpassword_css.css('background-image', "url('files/resources/images/closed_eye.png')");
            }
          });
        });
      </script>
    </div>
  </body>
</html>
