document.addEventListener("DOMContentLoaded", function () {
  const submitButton = document.getElementById("submit");
  const commandInput = document.getElementById("command");
  const outputDiv = document.getElementById("output");

  const freddyAudio = new Audio('files/resources/musics/freddy_nouse.mp3');
  const fnafBeatboxAudio = new Audio('files/resources/musics/fnaf_beatbox_1.mp3');
  const asrielAudio = new Audio('files/resources/musics/asriel.mp3');
  const undertaleAudio = new Audio('files/resources/musics/undertale.mp3');

  function stopAndResetAllAudio() {
    [undertaleAudio, freddyAudio, fnafBeatboxAudio, asrielAudio].forEach(a => {
      a.pause();
      a.currentTime = 0;
    });
  }

  function addCSS(css) {
    const style = document.createElement("style");
    style.innerHTML = css;
    document.head.appendChild(style);
  }

  submitButton.addEventListener("click", async function () {
    stopAndResetAllAudio();
    const command = commandInput.value.trim();
    if (!command) return;

    try {
      const response = await fetch("files/php/promo_codes.php", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ promo: command, csrf_token: window.CSRF_TOKEN })
      });

      const result = await response.json();
      outputDiv.innerHTML = "";

      if (result.status === "success") {
        if (result.message.includes("http")) {
          window.open(result.message, "_self");
        } else {
          addCSS(".promo_text_good{ position: absolute; left: 25%; top: 54%; font-weight: bolder; font-size: 35px; color: yellow; text-align: center; }");
          outputDiv.innerHTML = `<p class='promo_text_good'>${result.message}</p>`;
          
          if (result.promo.includes('toby')) {
            undertaleAudio.play();
          } else if (result.promo.includes('scott')) {
            freddyAudio.play();
            fnafBeatboxAudio.play();
          }
        }
      }
      else if (result.status === "error") {
        if (result.message.startsWith("Too many attempts")) {
          Alert.error('Error! Too Many Attempts. Wait before trying again.', 'Blocked', { displayDuration: 4000 });
        } 
        else if (result.message === "Invalid request method.") {
          Alert.error('Error! PHP Request Failed.', 'Error', { displayDuration: 4000 });
        } 
        else if (result.message === "Invalid promo code.") {
          asrielAudio.play();
          addCSS(".promo_text_bad_1{ position: absolute; left: 44%; top: 54%; font-weight: bolder; font-size: 35px; color: red; }");
          outputDiv.innerHTML = `<p class='promo_text_bad_1'>'${command}' is a wrong promo-code.</p>`;
        } 
        else if (result.message === "Error opening file.") {
          Alert.error('Error! Connecting To Database.', 'Error', { displayDuration: 4000 });
        } 
        else {
          Alert.error('Error! Something Went Wrong: ' + result.message, 'Error', { displayDuration: 4000 });
        }
      }
    } catch (error) {
      Alert.error('Error! Something Went Wrong. Error Message: ' + error, 'Error', { displayDuration: 4000 });
    }
    commandInput.value = "";
  });

  document.addEventListener('keyup', function (event) {
    if (event.code === 'Enter') {
      submitButton.click();
    }
  });
});
