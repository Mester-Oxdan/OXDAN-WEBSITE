document.addEventListener('DOMContentLoaded', function() {
  var video = document.getElementById('video');
  video.addEventListener('ended', function() {
      skipVideo();
  });
  var textPrompt = document.getElementById('textPrompt');
  var videoContainer = document.getElementById('videoContainer');
  var video = document.getElementById('video');
  var lets_start = true;
  var can_skip = true;

  function stopVideo() {
    video.pause();
    video.currentTime = 0;
  }

  function replaceVideoSource(newSource) {
    can_skip = false;
    video.src = newSource;
  }

  function skipVideo() {
    fully_begin();
    can_skip = false;
    stopVideo();
    replaceVideoSource('../files/resources/video/oxdan_intro_last_part.mp4');
    video.play();
  }

  function redirectTo(page) {
    const routes = {
      'home_login': '/home_login'
    };
    window.location.href = routes[page];
  }

  function fully_begin() {
    function skipVideo_2() {
      document.removeEventListener('keypress', handleKeyPress_2);
      document.removeEventListener('click', handleClick_2);
      redirectTo('home_login');
    }

    function handleKeyPress_2(event) {
        skipVideo_2();
    }

    function handleClick_2(event) {
        skipVideo_2();
    }

    function Moving_on() {
        document.addEventListener('keypress', handleKeyPress_2);
        document.addEventListener('click', handleClick_2);
    }
    setTimeout(Moving_on, 6300);
  }
  
  function showVideo() {
    if (can_skip) {
        function handleKeyPress(event) {
            if (event.key === 'c' || event.key === 'C') {
              document.removeEventListener('keypress', handleKeyPress);
            document.removeEventListener('click', handleClick);
                skipVideo();
            }
        }

        function handleClick(event) {
          document.removeEventListener('keypress', handleKeyPress);
          document.removeEventListener('click', handleClick);
          skipVideo();
        }
        document.addEventListener('keypress', handleKeyPress);
        document.addEventListener('click', handleClick);
    } 
    textPrompt.style.display = 'none';
    videoContainer.style.display = 'flex';
    video.play();
  }
    
  function before_show_video() {
    if (lets_start) {
      var audio = new Audio('../files/resources/musics/start_intro.mp3');
      audio.play();
      body.style.animationName = 'example';
      body.style.animationDuration = '5.3s';
      body.style.animationFillMode = 'forwards';
      lets_start = false;
      setTimeout(showVideo, 5300);
    }
  }
  document.addEventListener('click', before_show_video);
  document.addEventListener('keydown', function(event) {
      before_show_video();
    });
});
