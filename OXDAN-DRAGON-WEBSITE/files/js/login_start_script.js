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
    
    fetch("files/php/oauth_google.php", {
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
            window.location.href = "/skip_login";
        } else {
            alert("Google login failed: " + data.message);
        }
    });
}

const waitForGoogle = setInterval(() => {
    if (window.google && google.accounts && google.accounts.id) {
        clearInterval(waitForGoogle);
        startGoogleLogin();
    }
}, 50);

$(document).ready(function() {
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
});

document.addEventListener("DOMContentLoaded", function () {
    const form = document.getElementById("login-form");
    if (form) {
        form.addEventListener("submit", login);
    }
});

function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function saveUsernameToTextFile() {
    await delay(4000);
    function redirectTo(page) {
        const routes = {
            'skip_login': '/skip_login'
        };
    window.location.href = routes[page];
    }
    redirectTo('skip_login');
}

function handleSuccessfulLogin() {
    saveUsernameToTextFile();
}

var widgetId1;
var onloadCallback = function() {
    widgetId1 = grecaptcha.render('example1', {
        'sitekey': window.RECAPTCHA_SITE_KEY,
        'theme': 'light',
        'callback': function(response) {
            document.querySelector("#login-form button[type='submit']").disabled = false;
        },
        'expired-callback': function() {
            document.querySelector("#login-form button[type='submit']").disabled = true;
        }
    });
};

function login(event) {
    event.preventDefault();

    if (window.loginIsSubmitting) return;
    window.loginIsSubmitting = true;
    var submitButton = document.querySelector("#login-form button[type='submit']");
    submitButton.disabled = true;
    var usernameInput = document.getElementById('username');
    var passwordInput = document.getElementById('password');
    var usernameOrEmail = usernameInput.value;
    var password = passwordInput.value;

    if (typeof grecaptcha === 'undefined' || typeof widgetId1 === 'undefined') {
        Alert.error('Error! reCAPTCHA not loaded. Please refresh the page.', 'Error', { displayDuration: 4000 });
        window.loginIsSubmitting = false;
        submitButton.disabled = false;
        return;
    }

    var recaptchaResponse = grecaptcha.getResponse(widgetId1);

    if (!recaptchaResponse) {
        Alert.error('Error! Please confirm you are not a robot.', 'Error', { displayDuration: 4000 });
        window.loginIsSubmitting = false;
        submitButton.disabled = false;
        return;
    }

    var deviceInfo = {
        userAgent: navigator.userAgent,
        screenResolution: window.screen.width + "x" + window.screen.height
    };

    var loginData = {
        usernameOrEmail: usernameOrEmail,
        password: password,
        deviceInfo: deviceInfo,
        csrf_token: window.CSRF_TOKEN,
        recaptcha_response: recaptchaResponse
    };

    fetch('../files/php/login.php', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(loginData)
    })
    .then(response => response.json())
    .then(result => {
        const responseDiv = document.getElementById('response');
        responseDiv.innerHTML = '';
        if (result.status === 'success') {
            Alert.success('Success! Wait 4 Seconds Before You Will Move On.', 'Success', { displayDuration: 4000 });
            handleSuccessfulLogin();
        } else if (result.status === 'error') {
            handleLoginError(result.message, usernameOrEmail);
        }
    })
    .catch(error => {
        handleLoginError('Network error: ' + error.message, usernameOrEmail);
    })
    .finally(() => {
        window.loginIsSubmitting = false;
        submitButton.disabled = false;
        grecaptcha.reset(widgetId1);
    });
}

function handleLoginError(message, usernameOrEmail) {
    if (typeof grecaptcha !== 'undefined' && widgetId1 !== undefined) {
        grecaptcha.reset(widgetId1);
    }
    
    Alert.error('Error! ' + message, 'Error', { displayDuration: 4000 });

    if (message === 'Invalid credentials.' || message === 'User not found.') {
        Alert.info('Info Hint! If you forgot your password, follow this link: <a href="javascript:void(0)" onclick="requestPasswordReset(\'' + usernameOrEmail + '\')">Reset Password</a>', 'Info', { displayDuration: 4000 });
    }
}

function getRateLimitMessage(attempt) {
    const messages = {
        1: 'Too many attempts. Wait 1 minute before trying again.',
        2: 'Too many attempts. Wait 5 minutes before trying again.',
        3: 'Too many attempts. Wait 10 minutes before trying again.',
        4: 'Too many attempts. Wait 15 minutes before trying again.'
    };
    return messages[attempt] || 'Too many attempts. Please try again later.';
}

function requestPasswordReset(email) {
    if (!email) {
        Alert.error('Error! Please enter your email/username first.', 'Error', { displayDuration: 4000 });
        return;
    }

    Alert.info('Sending password reset code...', 'Info', { displayDuration: 2000 });

    fetch('../files/php/send_verification.php', {
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