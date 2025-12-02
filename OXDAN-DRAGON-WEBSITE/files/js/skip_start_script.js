document.addEventListener("DOMContentLoaded", () => {
  const form = document.querySelector("#formContainer form");
  const btn = form.querySelector("button");
  const post = document.querySelector(".text");
  const widget = document.querySelector(".star-widget");
  const textarea = document.querySelector(".textarea textarea");

  post.style.display = "none";

  btn.addEventListener("click", function (event) {
    event.preventDefault();
    submitRating();
  });

  function submitRating() {
    if (window.isSubmittingRating) return;
    window.isSubmittingRating = true;

    const ratingInput = document.querySelector('.star-widget input[type="radio"]:checked');
    const feedback = textarea.value.trim();

    if (!ratingInput) {
      Alert.error('Error! You Forgot To Rate Us.', 'Error', { displayDuration: 4000 });
      window.isSubmittingRating = false;
      return;
    }
    if (feedback === "") {
      Alert.error('Error! You Forgot Describe Your Experience.', 'Error', { displayDuration: 4000 });
      window.isSubmittingRating = false;
      return;
    }

    const ratingValue = ratingInput.value;

    const formData = new FormData();
    formData.append("rate", ratingValue);
    formData.append("feedback", feedback);

    fetch("files/php/submit_rating.php", {
      method: "POST",
      body: formData
    })
    .then(response => response.json())
    .then(result => {
      if (result.status === "success") {
        Alert.success('Success! Thank You For Your Feedback ❤️', 'Success', { displayDuration: 4000 });
        widget.style.display = "none";
        textarea.style.display = "none";
        btn.style.display = "none";
        post.style.display = "block";
      } else if (result.status === "error") {
        window.isSubmittingRating = false;

        switch (result.message) {
          case 'Rating is required.':
            Alert.error('Error! Rating Is Required.', 'Error', { displayDuration: 4000 });
            break;
          case 'Invalid request method.':
            Alert.error('Error! PHP Request Failed.', 'Error', { displayDuration: 4000 });
            break;
          case 'You have reached the limit of feedback submissions.':
            Alert.error('Error! You Have Reached The Maximum Rating Limit.', 'Error', { displayDuration: 4000 });
            break;
          case 'Too many feedbacks for feedback_1':
            Alert.error('Error! Too Many Feedbacks. Wait 1 minute before trying again.', 'Error', { displayDuration: 4000 });
            break;
          case 'Too many feedbacks for feedback_2':
            Alert.error('Error! Too Many Feedbacks. Wait 5 minutes before trying again.', 'Error', { displayDuration: 4000 });
            break;
          case 'Too many feedbacks for feedback_3':
            Alert.error('Error! Too Many Feedbacks. Wait 30 minutes before trying again.', 'Error', { displayDuration: 4000 });
            break;
          case 'Too many feedbacks for feedback_4':
            Alert.error('Error! Too Many Feedbacks. Wait 1 hour before trying again.', 'Error', { displayDuration: 4000 });
            break;
          default:
            Alert.error('Error! Something Went Wrong: ' + result.message, 'Error', { displayDuration: 4000 });
        }
      }
    })
    .catch(error => {
      window.isSubmittingRating = false;
      Alert.error('Error! Something Went Wrong. Error Message: ' + error, 'Error', { displayDuration: 4000 });
    });
  }

  document.getElementById('halfBox').addEventListener('click', function() {
    const formContainer = document.getElementById('formContainer');
    formContainer.style.display = formContainer.style.display === 'block' ? 'none' : 'block';
  });
});
