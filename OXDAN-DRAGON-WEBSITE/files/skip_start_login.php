<?php include 'php/auth.php'; ?>
<!Doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title> MAIN MENU </title>
    <link id="logo-icon" rel="icon" type="image/png" href="files/resources/images/my_dragon_ico.ico">
    <link rel="stylesheet" href="files/css/minified/skip_start_login_style.min.css">
    <link rel="stylesheet" href="files/css/w3.css">
    <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.0.3/css/font-awesome.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
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
          return (month === 11 || month === 0 || month === 1) ? "winter" : "other";
        }
        
        function setFavicon(path) {
          const old = document.getElementById("logo-icon");
          if (old) old.remove();

          const link = document.createElement("link");
          link.id = "logo-icon";
          link.rel = "icon";
          link.type = "image/x-icon";
          link.href = path + "?v=" + Date.now();
          document.head.appendChild(link);
        }

        function updateSeasonalImages(season) {
          const leftImgs = document.querySelectorAll('.column_left_img img');
          const rightImgs = document.querySelectorAll('.column_right_img img');
          const winterSrc = "files/resources/images/my_dragon_icon_full_winter.jpg";
          const otherSrc  = "files/resources/images/my_dragon_icon_full.jpg";
          const chosenSrc = (season === "winter") ? winterSrc : otherSrc;
          [...leftImgs, ...rightImgs].forEach(img => {
            img.src = chosenSrc + "?v=" + Date.now();
          });
        }

        const currentSeason = getSeason(new Date());

        if (currentSeason === "winter") {
          setFavicon("files/resources/images/my_dragon_winter_ico.ico");
        } else {
          setFavicon("files/resources/images/my_dragon_ico.ico");
        }

        updateSeasonalImages(currentSeason);
      });
    </script>
  </head>
  <body onload="getUsernameFromServer_5(function(name) {document.getElementById('usernamePlaceholder').textContent = name;});">
    <div class="half-box" id="halfBox">Rate Us ⭐</div>
    <div class="container" id="formContainer">
      <div class="text">Thanks For Rating Us! ❤️</div>
      <form action="files/php/submit_rating.php" method="post">
        <input type="hidden" name="csrf_token" value="<?php echo $_SESSION['csrf_token'] ?? ''; ?>">
        <div class="star-widget">
          <input name="rate" type="radio" id="rate-5" value="5">
          <label for="rate-5" class="fas fa-star"></label>
          <input name="rate" type="radio" id="rate-4" value="4">
          <label for="rate-4" class="fas fa-star"></label>
          <input name="rate" type="radio" id="rate-3" value="3">
          <label for="rate-3" class="fas fa-star"></label>
          <input name="rate" type="radio" id="rate-2" value="2">
          <label for="rate-2" class="fas fa-star"></label>
          <input name="rate" type="radio" id="rate-1" value="1">
          <label for="rate-1" class="fas fa-star"></label>
          <div class="header_1"></div>
        </div>
        <div class="textarea">
          <textarea cols="30" placeholder="Describe your experience..." maxlength="150"></textarea>
        </div>
        <div class="btn">
          <button type="submit">Post</button>
        </div>
      </form>
      <script src="files/js/minified/skip_start_script.min.js"></script>
    </div>
    <audio id="mySound" src="files/resources/musics/undertale_shop.mp3"></audio>
    <audio id="mySound_2" src="files/resources/musics/undertale_shop.mp3"></audio>
    <div class="column_left_img">    
      <img src="files/resources/images/my_dragon_icon_full.jpg" style='alt: Show; left: 100vw; height: 150vh; width: 9vw; background-size: contain;' ><br>
      <img src="files/resources/images/my_dragon_icon_full.jpg" style='alt: Show; left: 100vw; height: 150vh; width: 9vw; background-size: contain;' >
    </div>
    <div class="column_right_img">
      <img src="files/resources/images/my_dragon_icon_full.jpg" style='alt: Show; left: 100vw; height: 150vh; width: 9vw; background-size: contain;'><br>
      <img src="files/resources/images/my_dragon_icon_full.jpg" style='alt: Show; left: 100vw; height: 150vh; width: 9vw; background-size: contain;'>
    </div>
    <div>
      <input type="checkbox" id="checkmark" style="position: absolute; left: 18vw; bottom: -16vh; z-index: 4; height: 4vh; width: 4vw;"></div>
      <div style='position: absolute; left: 23vw; bottom: -18vh; z-index: 3; font-size: min(2.3vw, 2.3vh); white-space: nowrap;'><a><br><a href="https://docs.google.com/document/d/1hHxuawuVX8bTFENoeNQP0q9BFuWlf6fUOVd23PFpXk0/edit?usp=sharing" target="_blank" style='font-family: Arial, sans-serif;'><a style='font-family: Arial, sans-serif;'>I agree to the terms and conditions on the following <br>link(</a></a><a href="https://docs.google.com/document/d/1hHxuawuVX8bTFENoeNQP0q9BFuWlf6fUOVd23PFpXk0/edit?usp=sharing" target="_blank" style='font-family: Arial, sans-serif;'>https://docs.google.com/document/d/1hHxuawuVX8bTFENoeNQP0q9BFuWlf6fUOVd23PFpXk0/edit?usp=sharing</a><a>).</a></div></a>
      <div class="bg-text_skip_button">
        <button class="base_button button_download_c_windows" id="downloadBtn_1" style='font-family: Arial, sans-serif;' disabled> DOWNLOAD C/C++ Dragon Console Windows </button>
        <button class="base_button button_download_python_windows" id="downloadBtn_2" style='font-family: Arial, sans-serif;' disabled> DOWNLOAD PYTHON Dragon Console Windows </button>
        <button class="base_button button_download_c_linux" style='font-family: Arial, sans-serif;' disabled> DOWNLOAD C/C++ Dragon Console Linux </button>
        <button class="base_button button_download_python_linux" style='font-family: Arial, sans-serif;' disabled> DOWNLOAD PYTHON Dragon Console Linux </button>
        <div id="modal_2" class="modal_2 hidden">
          <h2 style="color: black;">Download Options</h2>
          <a href="files/php/download_python_console_copy.php?file=installer" class="download-link">Download Setup</a>
          <a href="files/php/download_python_console_copy.php?file=files" class="download-link">Download Files Only</a>
          <button id="closeBtn_2">Close</button>
        </div>
        <div id="modal" class="modal hidden">
          <h2 style="color: black">Download Options</h2>
          <a href="files/php/download_c_console_copy.php?file=installer" class="download-link">Download Setup</a>
          <a href="files/php/download_c_console_copy.php?file=files" class="download-link">Download Files Only</a>
          <button id="closeBtn">Close</button>
        </div>
      </div>
    </div>
    <script>
      document.addEventListener('DOMContentLoaded', function() {
        var checkmark = document.getElementById('checkmark');
        var buttons = document.querySelectorAll('.base_button');

        checkmark.addEventListener('change', function() {
          var isChecked = this.checked;
          buttons.forEach(function(button) {
              button.disabled = !isChecked;
          });
          if (!isChecked) {
            document.getElementById('modal').classList.add('hidden');
            document.getElementById('modal_2').classList.add('hidden');
          }
        });

        document.getElementById('downloadBtn_1').addEventListener('click', function() {
          var element = document.querySelector('.modal_2');
          document.getElementById('modal_2').classList.add('hidden');
          setTimeout(function() {
            element.classList.remove('show');
          }, 500);

          var element = document.querySelector('.modal')
          setTimeout(function() {
            element.classList.add('show');
          }, 500);
          document.getElementById('modal').classList.remove('hidden');
        });

        document.getElementById('downloadBtn_2').addEventListener('click', function() {
          var element = document.querySelector('.modal');
          document.getElementById('modal').classList.add('hidden');
          setTimeout(function() {
            element.classList.remove('show');
          }, 500);

          var element = document.querySelector('.modal_2')
          setTimeout(function() {
            element.classList.add('show');
          }, 500);
          document.getElementById('modal_2').classList.remove('hidden');
        });

        document.getElementById('closeBtn').addEventListener('click', function() {
          var element = document.querySelector('.modal');
          document.getElementById('modal').classList.add('hidden');
          setTimeout(function() {
            element.classList.remove('show');
          }, 500); 
        });

        document.getElementById('closeBtn_2').addEventListener('click', function() {
          var element = document.querySelector('.modal_2');
          document.getElementById('modal_2').classList.add('hidden');
          setTimeout(function() {
            element.classList.remove('show');
          }, 500); 
        });
      });
    </script>
    <div>
      <div class="stars" id="stars-container"></div>
      <div id="average-score"></div>
      <div id="vote-count"></div>
    </div>
    <script>
      function fetchAndDisplayAverageScore() {
        fetch('files/php/calculate_ratings.php')
          .then(response => response.json())
          .then(data => {
            const averageScore = data.average_score;
            const roundedAverage = parseFloat(averageScore).toFixed(2);
            const fullStars = Math.floor(averageScore);
            const halfStar = (averageScore - fullStars) >= 0.5;
            const starsContainer = document.getElementById('stars-container');
            starsContainer.innerHTML = '';

            for (let i = 0; i < fullStars; i++) {
                starsContainer.innerHTML += '<i class="fas fa-star star"></i>';
            }

            if (halfStar) {
                starsContainer.innerHTML += '<i class="fas fa-star-half-alt star"></i>';
            }

            const emptyStars = 5 - Math.ceil(averageScore);
            for (let i = 0; i < emptyStars; i++) {
                starsContainer.innerHTML += '<i class="far fa-star star"></i>';
            }

            const averageScoreDiv = document.getElementById('average-score');
            averageScoreDiv.textContent = `${roundedAverage} / 5.00`;

            const voteCountDiv = document.getElementById('vote-count');
            voteCountDiv.textContent = `Votes: ${data.total_ratings}`;
          })
          .catch(error => {
            console.error('Error fetching data:', error);
          });
      }
      document.addEventListener('DOMContentLoaded', fetchAndDisplayAverageScore);
    </script>
    <form id="commentForm" class="form_container">
      <textarea id="comment" style="resize: none;" cols="30" name="comment" placeholder="Your Comment" maxlength="150" class="form_textarea" required></textarea>
      <button type="submit" class="form_button">Submit</button>
    </form>
    <div id="comments" class="comments_container"></div>
    <div class="nav-arrows">
      <button class="nav-arrow prev disabled">&larr; Previous</button>
      <button class="nav-arrow next">Next &rarr;</button>
    </div>
    <script>
      let currentCommentIndex = 0;
      const commentsPerPage = 4;

      function getUsernameFromServer_5(callback) {
        $.getJSON('files/php/get_username.php', function(data) {
          if (data.username) {
            callback(data.username);
          } else {
            Alert.error('Error! Username Not Found In Response', 'Error', { displayDuration: 4000 });
          }
        }).fail(function(jqXHR, textStatus, errorThrown) {
          console.error('Failed to fetch username:', textStatus, errorThrown);
        });
      }

      document.getElementById('commentForm').addEventListener('submit', function(e) {
        e.preventDefault();

        var formData = new FormData(this);
        formData.append('csrf_token', window.CSRF_TOKEN);
        
        fetch('files/php/save_comment.php', {
          method: 'POST',
          body: formData,
        })
        .then(response => response.json())
        .then(result => {
          if (result.status === 'success') {
            Alert.success('Success! ' + result.message, 'Success', { displayDuration: 4000 });
            loadComments();
            this.reset();
          } else {
            Alert.error('Error! ' + result.message, 'Error', { displayDuration: 4000 });
          }
        })
        .catch(error => {
          console.error('Error:', error);
          Alert.error('Error! An Unexpected Error Occurred.', 'Error', { displayDuration: 4000 });
        });
      });

      function loadComments() {
        fetch('files/php/fetch_comments.php')
          .then(response => response.json())
          .then(data => {
            const commentsDiv = document.getElementById('comments');
            commentsDiv.innerHTML = '';
            data.reverse();
            data.forEach((comment, index) => {
              const commentBox = document.createElement('div');
              commentBox.classList.add('comment_box');
              
              if (index >= currentCommentIndex && index < currentCommentIndex + commentsPerPage) {
                commentBox.classList.add('show');
              }
              
              const usernameSpan = document.createElement('span');
              usernameSpan.className = 'comment_username';
              usernameSpan.textContent = comment.username;
              
              const commentText = document.createElement('p');
              commentText.className = 'comment_text';
              commentText.textContent = comment.comment;
              
              const timestampSmall = document.createElement('small');
              timestampSmall.className = 'comment_timestamp';
              timestampSmall.textContent = comment.timestamp;
              
              commentBox.appendChild(usernameSpan);
              commentBox.appendChild(commentText);
              commentBox.appendChild(timestampSmall);
              
              commentsDiv.appendChild(commentBox);
            });
            updateNavArrows(data.length);
          });
      }
      function updateNavArrows(totalComments) {
        const prevBtn = document.querySelector('.nav-arrow.prev');
        const nextBtn = document.querySelector('.nav-arrow.next');

        if (currentCommentIndex === 0) {
          prevBtn.classList.add('disabled');
        } else {
          prevBtn.classList.remove('disabled');
        }

        if (currentCommentIndex + commentsPerPage >= totalComments) {
          nextBtn.classList.add('disabled');
        } else {
          nextBtn.classList.remove('disabled');
        }
      }
      document.querySelector('.nav-arrow.prev').addEventListener('click', function() {
        if (currentCommentIndex > 0) {
          currentCommentIndex -= commentsPerPage;
          loadComments();
        }
      });
      document.querySelector('.nav-arrow.next').addEventListener('click', function() {
        const totalComments = document.querySelectorAll('.comment_box').length;
        if (currentCommentIndex + commentsPerPage < totalComments) {
          currentCommentIndex += commentsPerPage;
          loadComments();
        }
      });
      document.addEventListener('DOMContentLoaded', function() {
        loadComments();
      });
    </script>
    <div class="bg-text_skip_upper_menu_bar">
      <div class="topnav">
        <a onclick="redirectTo('skip_login');" style='font-family: Arial, sans-serif;'>MENU</a>
        <a onclick="redirectTo('home_login');" style='font-family: Arial, sans-serif;'>HOME</a>
        <a onclick="redirectTo('register');" style='font-family: Arial, sans-serif;'>REGISTRATION</a>
        <a onclick="redirectTo('login');" style='font-family: Arial, sans-serif;'>LOGIN</a>
        <a onclick="redirectTo('promo_codes');" style='font-family: Arial, sans-serif;'>CODES</a>
        <a onclick="redirectTo('about_login');" style='font-family: Arial, sans-serif;'>ABOUT</a>
      </div>
      <script>
        function redirectTo(page) {
          const routes = {
            'skip_login': '/skip_login',
            'home_login': '/home_login',
            'register': '/register',
            'login': '/login',
            'promo_codes': '/promo_codes',
            'about_login': '/about_login'
          };
          window.location.href = routes[page];
        }
      </script>
      <div class="circle">
        <img id="profile-pic" src="files/resources/images/default_pict.png" alt="Profile Picture">
        <input type="file" id="upload-input" accept="image/*">
      </div>
      <span class="name_circle" id="usernamePlaceholder"></span>
      <script>
        $(document).ready(function () {
          $.getJSON('files/php/get_username.php', function(data) {
            $('#usernamePlaceholder').text(data.username);
          }).fail(function(jqXHR, textStatus, errorThrown) {
            console.error('Failed to fetch username:', textStatus, errorThrown);
          });
        });
      </script>
      <script src="files/js/minified/upload_pict_script.min.js"></script>  
    </div>
    <div class="bg-text_large_main">
      <a><b style='font-family: Arial, sans-serif;'>!ORIGINAL OXDAN DRAGON WEBSITE!</b></a>
    </div>
    <div class="bg-text">
      <a><b onclick="redirectTo('about');" style='font-family: Arial, sans-serif;'>About Author: </b><a style='font-family: Arial, sans-serif;'>Author of this console is</a> <b style='font-family: Arial, sans-serif;'>OXDAN PRADUCTION</b></a><a><img src="/../../files/resources/images/github_logo.png" alt="Github Logo" style="width: 2.3vw; height: 1.8vw; padding-left: 20px;"><b href="https://github.com/Mester-Oxdan" target="_blank" style="margin-left: 0.5em;" style='font-family: Arial, sans-serif;'><a style='font-family: Arial, sans-serif;'>Author Github: </a></b><a href="https://github.com/Mester-Oxdan" target="_blank" style='font-family: Arial, sans-serif;'>https://github.com/Mester-Oxdan</a>
      <a style='font-family: Arial, sans-serif;'><br><br><img src="/../../files/resources/images/gmail_logo.png" alt="Gmail Logo" style="width: 2.3vw; height: 1.8vw;"><b style='font-family: Arial, sans-serif; margin-left: 1%;'>Author Gmail: </b>bogerter4521de@gmail.com</a><img src="/../../files/resources/images/instagram_logo.png" alt="Gmail Logo" style="width: 2.3vw; height: 2.3vw; padding-left: 10px;"><b href="https://instagram.com/oxdanpraduction" target="_blank" style="margin-left: 1em;" style='font-family: Arial, sans-serif;'><a style='font-family: Arial, sans-serif;'>Author Instagram: </a></b><a href="https://instagram.com/oxdanpraduction" target="_blank" style='font-family: Arial, sans-serif;'>https://instagram.com/oxdanpraduction</a>
      <br><br><img src="/../../files/resources/images/youtube_logo.png" alt="Youtube Logo" style="width: 2.3vw; height: 1.8vw;"><b href="https://www.youtube.com/@Oxdan_Praduction" target="_blank" style='font-family: Arial, sans-serif; margin-left: 1%;'>Author Youtube: </b><a href="https://www.youtube.com/@Oxdan_Praduction" target="_blank" style='font-family: Arial, sans-serif;'>https://www.youtube.com/@Oxdan_Praduction</a><img src="/../../files/resources/images/kwork_logo.png" alt="Kwork Logo" style="width: 2.5vw; height: 2vw; padding-left: 10px;"><b href="https://kwork.com/user/jecob" target="_blank" style="margin-left: 1em;" style='font-family: Arial, sans-serif;'><a style='font-family: Arial, sans-serif;'>Author Kwork: </a></b><a href="https://kwork.com/user/jecob" target="_blank" style='font-family: Arial, sans-serif;'>https://kwork.com/user/jecob</a>
      <br><br><img src="/../../files/resources/images/tiktok_logo.png" alt="Tiktok Logo" style="width: 2.7vw; height: 2.2vw;"><b href="https://www.tiktok.com/@oxdan_praduction" target="_blank" style='font-family: Arial, sans-serif; margin-left: 1%;'>Author TikTok: </b><a href="https://www.tiktok.com/@oxdan_praduction" target="_blank" style='font-family: Arial, sans-serif;'>www.tiktok.com/@oxdan_praduction</a><img src="/../../files/resources/images/fiverr_logo.png" alt="Fiverr Logo" style="width: 5.5vw; height: 2.7vw; padding-left: 10px;"><b href="https://www.fiverr.com/jecob_567" target="_blank" style='font-family: Arial, sans-serif;'><a style='font-family: Arial, sans-serif;'>Author Fiverr :</a></b><a href="https://www.fiverr.com/jecob_567" target="_blank" style='font-family: Arial, sans-serif;'>https://www.fiverr.com/jecob_567</a>
      <br><br><b style='font-family: Arial, sans-serif;'>Photos 2025:</b></a>
    </div>
    <div class="bg-text_images_screens" style="z-index: 5;">
      <div class="w3-row-padding">
        <div class="w3-container w3-third">
          <img src="files/resources/images/dragon_console_images/Console_Start_Menu.webp" style="width: 23vw; height: 25.5vh; position:absolute; left: -2vw; cursor:pointer" onclick="onClick(this)" class="w3-hover-opacity">
        </div>
        <div class="w3-container w3-third">
          <img src="files/resources/images/dragon_console_images/Console_Rules.webp" style="width: 23vw; height: 25.5vh; position:absolute; left: 22vw; cursor:pointer" onclick="onClick(this)" class="w3-hover-opacity">
        </div>
        <div class="w3-container w3-third">
          <img src="files/resources/images/dragon_console_images/Console_Start.webp" style="width: 23vw; height: 25.5vh; position:absolute; left: 46vw; cursor:pointer" onclick="onClick(this)" class="w3-hover-opacity">
        </div>
        <div class="w3-container w3-third">
          <img src="files/resources/images/dragon_console_images/Console_Commands.webp" style="width: 23vw; height: 25.5vh; position:absolute; left: 10.1vw; top: 26vh; cursor:pointer" onclick="onClick(this)" class="w3-hover-opacity">
        </div>
        <div class="w3-container w3-third">
          <img src="files/resources/images/dragon_console_images/Console_Author_Command.webp" style="width: 23vw; height: 25.5vh; position:absolute; left: 34.1vw; top: 26vh; cursor:pointer" onclick="onClick(this)" class="w3-hover-opacity">
        </div>
      </div>
      <div id="modal01" class="w3-modal" onclick="this.style.display='none'">
        <span class="w3-button w3-hover-red w3-xlarge w3-display-topright">&times;</span>
        <div class="w3-modal-content w3-animate-zoom">
          <img id="img01" style="width:100%">
        </div>
      </div>
      <script>
        function onClick(element) {
          document.getElementById("img01").src = element.src;
          document.getElementById("modal01").style.display = "block";
        }
      </script>
    </div>
    <div class="bg-text_button">
      <a style='font-family: Arial, sans-serif; font-size: min(2.3vw, 2.3vh); white-space: nowrap;'>Author create this console for learning coding, don't use it in bad purposes.</a>
    </div>
    <div style='position: absolute; left: 28.7vw; bottom: -5vh; font-size: min(2.3vw, 2.3vh); white-space: nowrap;'><a><br><a href="https://github.com/Mester-Oxdan" target="_blank" style='font-family: Arial, sans-serif;'><a style='font-family: Arial, sans-serif;'>You can find code of this console on Author github(</a></a><a href="https://github.com/Mester-Oxdan" target="_blank" style='font-family: Arial, sans-serif;'>https://github.com/Mester-Oxdan</a><a>).</a></div></a>
  </body>
</html>
