<?php include 'php/auth.php'; ?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CONFIRM EMAIL</title>
    <link id="logo-icon" rel="icon" type="image/png" href="files/resources/images/my_dragon_ico.ico">
    <link rel="stylesheet" type="text/css" href="files/css/minified/confirm_email_style.min.css">
    <script src="files/js/minified/confirm_email_start_script.min.js"></script>
    <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.0.3/css/font-awesome.min.css">
    <script src="files/js/jquery.js"></script>
    <script src="files/js/minified/alert_system_script.min.js"></script>
    <script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-2281387454588748" crossorigin="anonymous"></script>
    <script>
      window.CSRF_TOKEN = '<?php echo $_SESSION["csrf_token"] ?? ""; ?>';
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
      <h2>CONFIRM YOUR EMAIL</h2>
      <form onsubmit="confirm_email(event)">
        <label for="code">Code:</label>
        <input type="text" id="code" maxlength="60" required>
        <div class="resend-wrapper">
          <span id="resend-timer">Resend available in <span id="countdown">60</span>s</span>
          <span id="resend-link" class="hidden">Resend email</span>
        </div>
        <button type="submit">Submit</button>
      </form>
      <div id="response"></div>
    </div>
  </body>
</html>
