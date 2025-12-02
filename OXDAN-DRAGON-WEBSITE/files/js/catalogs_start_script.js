let leftArrow, rightArrow, zoomedLeftArrow, zoomedRightArrow;

document.addEventListener("DOMContentLoaded", function() {
  leftArrow = document.createElement("span");
  leftArrow.innerHTML = "&#10094;";
  leftArrow.classList.add("arrow", "left");
  leftArrow.addEventListener("click", function() {
    currentIndex = (currentIndex - 1 + thumbnails.length) % thumbnails.length;
    showMedia(thumbnails[currentIndex].src);
    thumbnails.currentIndex.classList.add("active");
  });
  
  rightArrow = document.createElement("span");
  rightArrow.innerHTML = "&#10095;";
  rightArrow.classList.add("arrow", "right");
  rightArrow.addEventListener("click", function() {
    currentIndex = (currentIndex + 1) % thumbnails.length;
    showMedia(thumbnails[currentIndex].src);
  });

  zoomedLeftArrow = document.createElement("span");
  zoomedLeftArrow.innerHTML = "&#10094;";
  zoomedLeftArrow.classList.add("arrow", "left_2");
  zoomedLeftArrow.addEventListener("click", function() {
    currentIndex = (currentIndex - 1 + thumbnails.length) % thumbnails.length;
    showZoomedMedia(thumbnails[currentIndex].src);
  });

  zoomedRightArrow = document.createElement("span");
  zoomedRightArrow.innerHTML = "&#10095;";
  zoomedRightArrow.classList.add("arrow", "right_2");
  zoomedRightArrow.addEventListener("click", function() {
    currentIndex = (currentIndex + 1) % thumbnails.length;
    showZoomedMedia(thumbnails[currentIndex].src);
  });

  const buttonBuy = document.getElementById("slideButton");
  const slideBox = document.getElementById("slideBox");

  buttonBuy.addEventListener("click", function() {
    if (slideBox.classList.contains("show")) {
      slideBox.classList.remove("show");
    } else {
      slideBox.classList.add("show");
    }
  });

  const thumbnails = document.querySelectorAll(".catalog-media img, .catalog-media video");
  const mainMedia = document.querySelector(".main-media");
  const overlay = document.createElement("div");
  overlay.classList.add("overlay");
  let currentIndex = 0;
  let mediaElement;

  thumbnails.forEach((thumbnail, index) => {
    thumbnail.addEventListener("click", function() {
      thumbnails.forEach(thumb => {
        thumb.classList.remove("active");
      });
      this.classList.add("active");
      currentIndex = index;
      mainMedia.innerHTML = "";
      if (this.nodeName === 'VIDEO') {
        mediaElement = document.createElement("video");
        mediaElement.src = this.src;
        mediaElement.controls = true;
        mainMedia.appendChild(mediaElement);
      } else {
        const image = document.createElement("img");
        image.src = this.src;
        image.addEventListener("click", function() {
          showZoomedMedia(image.src);
        });
        mainMedia.appendChild(image);
      }
      showNormalArrows();
    });
  });

  let searchHistory = [];

  function addToSearchHistory(itemName) {
    searchHistory = searchHistory.filter(item => item !== itemName);
    searchHistory.unshift(itemName);
    saveSearchHistory();
  }

  function saveSearchHistory() {
      localStorage.setItem('searchHistory', JSON.stringify(searchHistory));
  }

  function displayAllProducts(category) {
    const searchResults = document.getElementById('searchResults');
    if (!searchResults) {
      return;
    }
    searchResults.innerHTML = '';
    const filteredProducts = category === 'all' || category === '' ? products : products.filter(product => product.category.includes(category));
    filteredProducts.forEach(product => {
      const itemContainer = createItemContainer(product);
      searchResults.appendChild(itemContainer);
    });
  }

  function createItemContainer(product) {
    const itemContainer = document.createElement('div');
    itemContainer.classList.add('search-item');
    itemContainer.style.backgroundImage = `url(${product.image})`;
    itemContainer.style.backgroundSize = 'cover';
    itemContainer.style.backgroundPosition = 'center';
    itemContainer.style.cursor = 'pointer';
    itemContainer.style.zIndex = '1';

    const name = document.createElement('a');
    name.innerHTML = product.name;
    itemContainer.appendChild(name);

    const price = document.createElement('b');
    price.innerHTML = product.price;
    itemContainer.appendChild(price);

    const description = document.createElement('p');
    description.innerHTML = product.description;
    itemContainer.appendChild(description);

    const heartButton = document.createElement('button');
    heartButton.classList.add('like-button');
    heartButton.innerHTML = `
    <div class="like-wrapper">
        <div class="ripple"></div>
        <svg class="heart" width="24" height="24" viewBox="0 0 24 24">
          <path d="M12,21.35L10.55,20.03C5.4,15.36 2,12.27 2,8.5C2,5.41 4.42,3 7.5,3C9.24,3 10.91,3.81 12,5.08C13.09,3.81 14.76,3 16.5,3C19.58,3 22,5.41 22,8.5C22,12.27 18.6,15.36 13.45,20.03L12,21.35Z"></path>
        </svg>
        <div class="particles" style="--total-particles: 6">
          <div class="particle" style="--i: 1; --color: #7642F0"></div>
          <div class="particle" style="--i: 2; --color: #AFD27F"></div>
          <div class="particle" style="--i: 3; --color: #DE8F4F"></div>
          <div class="particle" style="--i: 4; --color: #D0516B"></div>
          <div class="particle" style="--i: 5; --color: #5686F2"></div>
          <div class="particle" style="--i: 6; --color: #D53EF3"></div>
        </div>
    </div>`;

    heartButton.style.right = "10px";

    getFavoriteStateDB(product.number).then(isFavorite => {
      if (isFavorite) {
        heartButton.classList.add('active');
      } else {
        heartButton.classList.remove('active');
      }
    });

    heartButton.addEventListener('click', async (event) => {
      event.stopPropagation();
      
      const newState = await toggleFavoriteDB(product.number);
      if (newState !== null) {
        if (newState) {
          heartButton.classList.add('active');
        } else {
          heartButton.classList.remove('active');
        }
      }
    });

    itemContainer.appendChild(heartButton);
    itemContainer.addEventListener('click', () => {
      addToSearchHistory(product.name);
      window.location.href = getProductLink(product);
    });

    return itemContainer;
  }

  displayAllProducts('all');

  function getProductLink(product) {
    return `../${product.url}`;
  }

  overlay.addEventListener("click", function(event) {
    if (event.target === overlay) {
      hideZoomedMedia();
    }
  });

  const closeBtn = document.createElement("span");
  closeBtn.innerHTML = "&times;";
  closeBtn.classList.add("close");
  overlay.appendChild(closeBtn);
  closeBtn.addEventListener("click", function() {
    hideZoomedMedia();
  });

  function showZoomedMedia(src) {
    overlay.innerHTML = "";
    if (src.endsWith('.mp4')) {
      mediaElement = document.createElement("video");
      mediaElement.src = src;
      mediaElement.controls = true;
      mediaElement.autoplay = true;
      mediaElement.loop = true;
    } else {
      mediaElement = document.createElement("img");
      mediaElement.src = src;
      mediaElement.classList.add("zoom-media");
    }
    overlay.appendChild(mediaElement);
    overlay.appendChild(zoomedLeftArrow);
    overlay.appendChild(zoomedRightArrow);
    document.body.appendChild(overlay);
    overlay.classList.add("active");
    hideNormalArrows();
  }

  function hideZoomedMedia() {
    overlay.classList.remove("active");
    overlay.innerHTML = "";
    showNormalArrows();
  }

  mainMedia.addEventListener('click', function(event) {
    if (event.target.nodeName === 'IMG' || event.target.nodeName === 'VIDEO') {
      showZoomedMedia(event.target.src);
    }
  });

  document.addEventListener('keydown', function(event) {
    if (event.key === 'ArrowLeft') {
      currentIndex = (currentIndex - 1 + thumbnails.length) % thumbnails.length;
      if (overlay.classList.contains('active')) {
        showZoomedMedia(thumbnails[currentIndex].src);
      } else {
        showMedia(thumbnails[currentIndex].src);
      }
    } else if (event.key === 'ArrowRight') {
      currentIndex = (currentIndex + 1) % thumbnails.length;
      if (overlay.classList.contains('active')) {
        showZoomedMedia(thumbnails[currentIndex].src);
      } else {
        showMedia(thumbnails[currentIndex].src);
      }
    }
  });

  function showMedia(src) {
    mainMedia.innerHTML = "";
    if (src.endsWith('.mp4')) {
      mediaElement = document.createElement("video");
      mediaElement.src = src;
      mediaElement.controls = true;
      mainMedia.appendChild(mediaElement);
    } else {
      const image = document.createElement("img");
      image.src = src;
      mainMedia.appendChild(image);
    }
    showNormalArrows();
  }

  function showNormalArrows() {
    mainMedia.appendChild(leftArrow);
    mainMedia.appendChild(rightArrow);
  }

  function hideNormalArrows() {
    if (mainMedia.contains(leftArrow)) {
      mainMedia.removeChild(leftArrow);
    }
    if (mainMedia.contains(rightArrow)) {
      mainMedia.removeChild(rightArrow);
    }
  }
});
