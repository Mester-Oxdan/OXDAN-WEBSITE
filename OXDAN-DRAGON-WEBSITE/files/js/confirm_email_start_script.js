async function confirm_email(event) {
  event.preventDefault();
  const codeInput = document.getElementById('code');
  const code = codeInput.value;
  const confirmData = { code, csrf_token: window.CSRF_TOKEN };

  fetch('../files/php/confirm_email.php', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(confirmData)
  })
  .then(response => response.json())
  .then(result => {
    const responseDiv = document.getElementById('response');
    responseDiv.innerHTML = '';

    if (result.status === 'success') {
      const h2 = document.createElement('h2');
      const paragraph = document.createElement('h2');
      const audio = new Audio('../files/resources/musics/undertale.mp3');

      Alert.success('Success! Registration successful.', 'Success', { displayDuration: 4000 });
      h2.textContent = '!Registration Successful!';
      paragraph.textContent = 'Press any key to continue';
      responseDiv.appendChild(h2);
      responseDiv.appendChild(paragraph);
      audio.play();

      function redirectTo(page) {
        const routes = { 'start': '/start' };
        window.location.href = routes[page];
      }

      document.addEventListener('keydown', () => redirectTo('start'));
      document.addEventListener('mousedown', () => redirectTo('start'));
    } 
    else if (result.status === 'blocked') {
      startBlockedCountdown(result.remaining);
      Alert.error(result.message, 'Blocked', { displayDuration: 4000 });
    }
    else if (result.status === 'error') {
      if (result.message === 'Error wrong code.') {
        Alert.error('Error! Wrong Code.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'User not found.') {
        Alert.error('Error! User Not Found.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Invalid request method.') {
        Alert.error('Error! Invalid Request Method.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Error opening file.') {
        Alert.error('Error! Connecting To Database.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Error writing to file.') {
        Alert.error('Error! Writing To Database.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Too many attempts for confirm_email_1') {
        Alert.error('Error! Too Many Attempts. Wait 1 minute before trying again.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Too many attempts for confirm_email_2') {
        Alert.error('Error! Too Many Attempts. Wait 5 minute before trying again.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Too many attempts for confirm_email_3') {
        Alert.error('Error! Too Many Attempts. Wait 10 minute before trying again.', 'Error', { displayDuration: 4000 });
      } else if (result.message === 'Too many attempts for confirm_email_4') {
        Alert.error('Error! Too Many Attempts. Wait 15 minute before trying again.', 'Error', { displayDuration: 4000 });
      } else {
        Alert.error('Error! Email Confirmation Failed.', 'Error', { displayDuration: 6000 });
      }
    }
  })
  .catch(error => {
    Alert.error('Error! Something Went Wrong.', 'Error', { displayDuration: 4000 });
  });
}

let blockedInterval = null;
function startBlockedCountdown(seconds) {
  const codeInput = document.getElementById('code');
  const submitBtn = document.getElementById('confirm-btn');
  codeInput.disabled = true;
  submitBtn.disabled = true;

  blockedInterval = setInterval(() => {
    seconds--;
    codeInput.placeholder = `Blocked. Try again in ${seconds}s`;
    if (seconds <= 0) {
      clearInterval(blockedInterval);
      codeInput.disabled = false;
      submitBtn.disabled = false;
      codeInput.placeholder = 'Enter your code';
    }
  }, 1000);
}

let countdownSeconds = 60;
let countdownInterval = null;

document.addEventListener('DOMContentLoaded', () => {
  startCountdown();

  const resendLink = document.getElementById('resend-link');
  resendLink.addEventListener('click', () => {
    if (!resendLink.classList.contains('disabled') && !resendLink.classList.contains('hidden')) {
      resendEmail();
    } else {
      Alert.info('Please Wait Until Timer Finishes.', 'Info', { displayDuration: 2500 });
    }
  });
});

function startCountdown() {
  const countdownElement = document.getElementById('countdown');
  const resendTimer = document.getElementById('resend-timer');
  const resendLink = document.getElementById('resend-link');

  resendLink.classList.add('disabled', 'hidden');
  resendLink.style.pointerEvents = 'none';
  resendLink.style.opacity = '0.5';
  resendTimer.classList.remove('hidden');

  countdownSeconds = 60;
  countdownElement.textContent = countdownSeconds;

  if (countdownInterval) clearInterval(countdownInterval);

  countdownInterval = setInterval(() => {
    countdownSeconds--;
    countdownElement.textContent = countdownSeconds;
    if (countdownSeconds <= 0) {
      clearInterval(countdownInterval);
      resendTimer.classList.add('hidden');
      resendLink.classList.remove('hidden', 'disabled');
      resendLink.style.pointerEvents = 'auto';
      resendLink.style.opacity = '1';
    }
  }, 1000);
}

function resendEmail() {
  const resendLink = document.getElementById('resend-link');

  resendLink.classList.add('disabled');
  resendLink.style.pointerEvents = 'none';
  resendLink.style.opacity = '0.5';

  fetch('../files/php/resend_email.php', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ type: 'confirm', csrf_token: window.CSRF_TOKEN })
  })
  .then(res => res.json())
  .then(data => {
    if (data.status === 'success') {
      Alert.success('New Confirmation Email Sent Successfully.', 'Success', { displayDuration: 4000 });
      startCountdown();
    } else {
      Alert.error('Error! ' + (data.message || 'Failed To Resend Email.'), 'Error', { displayDuration: 4000 });
      resendLink.classList.remove('disabled');
      resendLink.style.pointerEvents = 'auto';
      resendLink.style.opacity = '1';
    }
  })
  .catch(err => {
    Alert.error('Error! Something Went Wrong.', 'Error', { displayDuration: 4000 });
    resendLink.classList.remove('disabled');
    resendLink.style.pointerEvents = 'auto';
    resendLink.style.opacity = '1';
  });
}
