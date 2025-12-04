var widgetId1;

var onloadCallback = function() {
  widgetId1 = grecaptcha.render('example2', {
    'sitekey': window.RECAPTCHA_SITE_KEY,
    'theme': 'light'
  });
};

$(document).ready(function() {
  $('#register_form').on('submit', register);
  
  $('#showPasswordLabel').on('click', function() {
    var passwordInput = $('#password');
    var showpassword_css = $('#showPasswordLabel');

    if (passwordInput.attr('type') === 'password') {
      passwordInput.attr('type', 'text');
      showpassword_css.css('background-image', "url('files/resources/images/open_eye.png')");
    } else {
      passwordInput.attr('type', 'password');
      showpassword_css.css('background-image', "url('files/resources/images/closed_eye.png')");
    }
  });
  
  initializeGoogleLogin();
});

function register(event) {
  event.preventDefault();

  var usernameInput = document.getElementById('username');
  var emailInput = document.getElementById('email');
  var passwordInput = document.getElementById('password');

  var username = usernameInput.value;
  var email = emailInput.value;
  var password = passwordInput.value;

  if (username.includes('@')) {
    Alert.error('Error! Username cannot contain "@" symbol.', 'Error', { displayDuration: 4000 });
    return;
  }

  var recaptchaResponse = grecaptcha.getResponse(widgetId1);

  if (!recaptchaResponse) {
    Alert.error('Error! Please confirm you are not a robot.', 'Error', { displayDuration: 4000 });
    return;
  }

  var registrationData = {
    username: username,
    email: email,
    password: password,
    csrf_token: window.CSRF_TOKEN,
    recaptcha_response: recaptchaResponse
  };

  fetch('/api/register.php', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(registrationData)
  })
  .then(response => response.json())
  .then(result => {
    const responseDiv = document.getElementById('response');
    responseDiv.innerHTML = '';

    if (result.status === 'success') {
      if (result.message === 'Email sent successfully.') {
        Alert.success('Success! We sent email verification to your email.', 'Success', { displayDuration: 4000 });
        redirectTo('confirm_email');
      }
    } else if (result.status === 'error') {
      handleRegistrationError(result.message, email);
    }
  })
  .catch(error => {
    Alert.error('Error! Something went wrong.', 'Error', { displayDuration: 4000 });
  });
}

function handleRegistrationError(message, email) {
  if (typeof grecaptcha !== 'undefined' && widgetId1 !== undefined) {
    grecaptcha.reset(widgetId1);
  }
  Alert.error('Error! ' + message, 'Error', { displayDuration: 4000 });
  
  if (message === 'Username or email already taken.') {
    Alert.info('Info Hint! If you forgot your password, follow this link: <a href="javascript:void(0)" onclick="requestPasswordReset(\'' + email + '\')">Reset Password</a>', 'Info', { displayDuration: 4000 });
  }
}

function redirectTo(page) {
  const routes = {
    'confirm_email': '/confirm_email'
  };
  if (routes[page]) {
    window.location.href = routes[page];
  }
}

function requestPasswordReset(email) {
  if (!email) {
    Alert.error('Error! Please enter your email/username first.', 'Error', { displayDuration: 4000 });
    return;
  }

  Alert.info('Sending password reset code...', 'Info', { displayDuration: 2000 });

  fetch('/api/send_verification.php', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      email: email,
      csrf_token: window.CSRF_TOKEN
    })
  })
  .then(response => response.json())
  .then(data => {
    if (data.status === 'success') {
      Alert.success('Success! Password reset code sent. Redirecting...', 'Success', { displayDuration: 3000 });
      setTimeout(() => {
        window.location.href = '/confirm_email_new';
      }, 2000);
    } else {
      Alert.error('Error! ' + data.message, 'Error', { displayDuration: 4000 });
    }
  })
  .catch(error => {
    Alert.error('Error! Failed to send reset code.', 'Error', { displayDuration: 4000 });
  });
}

function initializeGoogleLogin() {
  if (!window.OAUTH_STATE) {
    return;
  }
  
  const waitForGoogle = setInterval(() => {
    if (window.google && google.accounts && google.accounts.id) {
      clearInterval(waitForGoogle);
      startGoogleLogin();
    }
  }, 50);
}

function startGoogleLogin() {
  const state = window.OAUTH_STATE;
  
  google.accounts.id.initialize({
    client_id: '204106058046-1f2lr09dtrsl6f1j26mvmtj8jut7p7tl.apps.googleusercontent.com',
    callback: handleCredentialResponse,
    state: state
  });
  
  google.accounts.id.renderButton(
    document.getElementById("google-login-btn"),
    { theme: "outline", size: "large" }
  );
}

function handleCredentialResponse(response) {
  const state = window.OAUTH_STATE;
  
  fetch("/api/oauth_google.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ 
          credential: response.credential,
          state: state
      })
  })
  .then(res => res.json())
  .then(data => {
      if (data.status === "success") {
        window.location.href = "/start";
      } else {
        alert("Google login failed: " + data.message);
      }
  });
}
