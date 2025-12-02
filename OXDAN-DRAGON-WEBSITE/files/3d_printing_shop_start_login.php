<?php include 'php/auth.php'; ?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>SHOP</title>
        <link id="logo-icon" rel="icon" type="image/png" href="files/resources/images/my_dragon_ico.ico">
        <link rel="stylesheet" href="files/css/minified/3d_printing_shop_style.min.css">
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
                }, 500)
            }
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
        <audio id="mySound" src="files/resources/musics/sans_shop.mp3"></audio>
        <audio id="mySound_2" src="files/resources/musics/sans_shop.mp3"></audio>
        <div class="container">
            <header>
                <div class="logo-image"></div>
                <h1 class="logo-text">Oxdan Shop</h1>
                <div class="search-bar">
                    <select id="categorySelect">
                        <option value="all">All Categories</option>
                        <option value="accessories">Accessories</option>
                        <option value="toys">Toys</option>
                        <option value="home_decor">Home Decor</option>
                        <option value="cosplay">Cosplay</option>
                    </select>
                    <input type="text" id="searchInput" placeholder="Search for a product..." oninput="showSuggestions()">
                    <button onclick="search()" id="test" style="white-space: nowrap;">Search 🔎</button>
                    <div class="toggle-switch">
                        <p>Suggestions</p>
                        <label class="switch">
                            <input type="checkbox" id="toggleSuggestions" onclick="toggleSuggestions()">
                            <span class="slider"></span>
                        </label>
                        <p style="margin-left: 1.4vw; white-space: nowrap;">Show Favorites</p>
                        <label class="switch">
                            <input type="checkbox" id="toggleFavorite">
                            <span class="slider"></span>
                        </label>
                    </div>
                    <a class="user_name">Hi, <span id="usernamePlaceholder"></span></a>
                    <div id="suggestions" class="suggestions"></div>
                    <script>
                        document.addEventListener('click', function(event) {
                            const suggestions = document.getElementById('suggestions');
                            const clickedElement = event.target;
                            if (!suggestions.contains(clickedElement) && clickedElement.id !== 'searchInput') {
                                suggestions.style.display = 'none';
                            }
                        });
                        $(document).ready(function () {
                            $.getJSON('files/php/get_username.php', function(data) {
                                $('#usernamePlaceholder').text(data.username);
                            }).fail(function(jqXHR, textStatus, errorThrown) {
                                console.error('Failed to fetch username:', textStatus, errorThrown);
                            });
                        });
                    </script>
                </div>
            </header>
            <div id="searchResults"></div>
        </div>
        <script src="../files/js/minified/3d_printing_shop_start_script.min.js"></script>
    </body>
</html>
