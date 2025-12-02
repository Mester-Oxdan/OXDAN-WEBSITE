<?php include 'php/auth.php'; ?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>HOME MENU</title>
        <link id="logo-icon" rel="icon" type="image/png" href="files/resources/images/my_dragon_ico.ico">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
        <link rel="stylesheet" href="files/css/minified/second_menu_login_style.min.css">
        <script src="files/js/jquery.js"></script>
        <script src="files/js/minified/alert_system_script.min.js"></script>
        <script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-2281387454588748" crossorigin="anonymous"></script>
        <script>
            window.CSRF_TOKEN = '<?php echo $_SESSION["csrf_token"] ?? ""; ?>';
            window.onload = function() {
                playSound();
            };
            function playSound() {
                setTimeout(() => {
                    document.getElementById('mySound').play();
                    document.getElementById('mySound').addEventListener('ended', function() {
                        document.getElementById('mySound_2').play();
                    });
                }, 500);
            }
            function Delete_confirmation(username) {
                const isGoogleUser = <?php echo ($_SESSION['oauth_provider'] ?? '') === 'google' ? 'true' : 'false'; ?>;
                
                if (isGoogleUser) {
                    if (confirm("Are you sure you want to delete " + username + "'s Google account? This action cannot be undone.")) {
                        deleteAccount(null);
                    }
                } else {
                    const password = prompt("Please enter your password to confirm account deletion:");
                    if (!password) return;
                    
                    if (confirm("Are you sure you want to delete " + username + "'s account? This action cannot be undone.")) {
                        deleteAccount(password);
                    }
                }
            }

            function deleteAccount(password) {
                fetch('../files/php/delete_account.php', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                        'X-Requested-With': 'XMLHttpRequest'
                    },
                    body: JSON.stringify({
                        confirm: true,
                        password: password,
                        csrf_token: window.CSRF_TOKEN
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.status === 'success') {
                        Alert.success('Success! Account Deleted Successfully!', 'Success', { displayDuration: 4000 });
                        window.location.href = data.redirect || '/start';
                    } else {
                        Alert.error('Error! ' + data.message, 'Error', { displayDuration: 4000 });
                    }
                })
                .catch(error => {
                    console.error('Error:', error);
                    Alert.error('Error! Deletion Failed.', 'Error', { displayDuration: 4000 });
                });
            }
            $(document).ready(function() {
                $.getJSON('files/php/get_username.php', function(data) {
                    if (data.username) {
                    $('#deleteAccountButton').on('click', function() {
                        Delete_confirmation(data.username);
                    });
                    } else {
                        Alert.error('Error! Username Not Found In Response', 'Error', { displayDuration: 4000 });
                    }
                }).fail(function(jqXHR, textStatus, errorThrown) {
                    console.error('Failed to fetch username:', textStatus, errorThrown);
                });
            });
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
        <audio id="mySound" src="files/resources/musics/Undertale-Start-Menu.mp3"></audio>
        <audio id="mySound_2" src="files/resources/musics/Undertale-Start-Menu.mp3"></audio>

        <div id="buttons_to_show" class="bg-text_skip_button">
            <a id="3dshopbutton" class="button button_3d_shop" onclick="redirectTo('3d_printing_shop_login');">3D PRINTING SHOP. 🛍️</a>
            <a id="consoleDragonButton" class="button button_Console_dragon" onclick="redirectTo('dragon_console_login');">OXDAN DRAGON CONSOLE. 🔥</a>
            <a id="listsButton" class="button button_list" onclick="redirectTo('lists');">LISTS. 📃</a>
            <a id="listsButton" class="button button_list" onclick="redirectTo('faq');">FAQ. </a>
            <a id="backButton" class="button button_list" onclick="redirectTo('change_password_login');">CHANGE PASSWORD. 🔑</a>
            <a id="backButton" class="button button_list" onclick="redirectTo('start');">SIGN OUT. </a>
            <a id="deleteAccountButton" class="button button_list" href="javascript:void(0)">DELETE ACCOUNT. ❌</a>
        </div>
        <script>
            function redirectTo(page) {
                const routes = {
                    '3d_printing_shop_login': '/3d_printing_shop_login',
                    'dragon_console_login': '/dragon_console_login',
                    'lists': '/lists',
                    'faq': '/faq',
                    'change_password_login': '/change_password_login',
                    'start': '/start'
                };
                window.location.href = routes[page];
            }
        </script>
    </body>
</html>
