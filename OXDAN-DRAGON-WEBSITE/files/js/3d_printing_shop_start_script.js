let products = [];

async function loadProducts(category = 'all', search = '') {
  const response = await fetch(`../files/php/get_products.php?category=${encodeURIComponent(category)}&search=${encodeURIComponent(search)}`);
  products = await response.json();
  displayAllProducts(category);
}

document.addEventListener('DOMContentLoaded', () => {
  loadProducts('all');
});

let searchHistory = [];

function getUserToken() {
  let token = localStorage.getItem('user_token');
  if (!token) {
    return null;
  }
  return token;
}

function getBasePath() {
  const currentPath = window.location.pathname;
  
  if (currentPath.includes('/catalogs_html/') || 
    currentPath.includes('/toys/') ||
    currentPath.includes('/key chains/') || 
    currentPath.includes('/flower pots/')) {
    return '../../php/';
  }
  else {
    return '../files/php/';
  }
}
const basePath = getBasePath();
async function generateSecureToken() {
  try {
    const response = await fetch(`${basePath}favorites_manager.php?action=generate_token`, {
      method: 'POST',
      credentials: 'include'
    });
    const result = await response.json();
    
    if (result.success) {
      localStorage.setItem('user_token', result.user_token);
      return result.user_token;
    }
    return null;
  } catch (error) {
    return null;
  }
}
async function toggleFavoriteDB(productId) {
  try {
    let userToken = getUserToken();
    
    const response = await fetch(`${basePath}favorites_manager.php?action=toggle`, {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      credentials: 'include',
      body: JSON.stringify({
        product_id: productId,
        user_token: userToken
      })
    });
    const result = await response.json();
    
    if (result.user_token) {
      localStorage.setItem('user_token', result.user_token);
    }
    
    return result.success ? result.favorite : null;
  } catch (error) {
    return null;
  }
}

async function getFavoriteStateDB(productId) {
  try {
    const userToken = getUserToken();
    if (!userToken) {
      return false;
    }
    
    const response = await fetch(`${basePath}favorites_manager.php?action=get&product_id=${productId}`, {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({ user_token: userToken })
    });
    
    const result = await response.json();
    return result.success ? result.favorite : false;
  } catch (error) {
    return false;
  }
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

function addToSearchHistory(itemName) {
  searchHistory = searchHistory.filter(item => item !== itemName);
  searchHistory.unshift(itemName);
  saveSearchHistory();
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
  description.innerHTML = product.description ? product.description : '';
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
          
          const toggleSwitch = document.getElementById('toggleFavorite');
          if (toggleSwitch.checked) {
            displayFavoriteProducts();
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

const categorySelect = document.getElementById('categorySelect');
if (categorySelect) {
  categorySelect.addEventListener('change', function() {
    search();
  });
}

function search() {
  const category = document.getElementById('categorySelect').value;
  const searchInput = document.getElementById('searchInput').value.trim().toLowerCase();
  const searchResults = document.getElementById('searchResults');
  const toggleSwitch = document.getElementById('toggleFavorite');

  searchResults.innerHTML = '';
  let foundProducts = products.filter(product => {
      if (category === 'all' || category === '') {
        return product.name.toLowerCase().startsWith(searchInput);
      } else if (product.category.includes(category)) {
        return product.name.toLowerCase().startsWith(searchInput);
      }
      return false;
  });

  if (toggleSwitch.checked) {
    foundProducts = foundProducts.filter(product => {
      const heartButton = product.heartButton;
      return heartButton && heartButton.classList.contains('active');
    });
  }

  if (foundProducts.length === 0) {
    searchResults.textContent = 'No items found. Please try another search term or category.';
  } else {
    foundProducts.forEach(product => {
      const itemContainer = createItemContainer(product);
      searchResults.appendChild(itemContainer);
    });
  }
}

document.addEventListener('DOMContentLoaded', function() {
  document.getElementById('test').click();
});

function saveSearchHistory() {
  localStorage.setItem('searchHistory', JSON.stringify(searchHistory));
}

function loadSearchHistory() {
  const storedHistory = localStorage.getItem('searchHistory');
  if (storedHistory) {
    searchHistory = JSON.parse(storedHistory);
    search();
  } else {
    displayAllProducts('all');
  }
}

loadSearchHistory();
document.getElementById('searchInput').addEventListener('keypress', function(event) {
if (event.key === 'Enter') {
  search();
}
});

let suggestionsEnabled = false;
function showSuggestions() {
  if (suggestionsEnabled != false) {
    const searchInput = document.getElementById('searchInput').value.toLowerCase();
    const suggestions = document.getElementById('suggestions');
    suggestions.innerHTML = '';
    const matchedProducts = products.filter(product => product.name.toLowerCase().includes(searchInput));
    if (searchInput !== '') {
      matchedProducts.forEach(product => {
        const suggestionItem = document.createElement('div');
        suggestionItem.textContent = product.name;
        suggestionItem.classList.add('suggestion');
        suggestionItem.onclick = () => {
          document.getElementById('searchInput').value = product.name;
          addToSearchHistory(product.name);
          search();
          suggestions.innerHTML = '';
        };
        suggestions.appendChild(suggestionItem);
      });
    }
    suggestions.style.display = 'block';
  }
}

function toggleSuggestions() {
  const toggleSwitch = document.getElementById('toggleSuggestions');
  const suggestions = document.getElementById('suggestions');

  if (toggleSwitch.checked) {
    suggestionsEnabled = true;
  } else {
    suggestionsEnabled = false;
  }
}

function toggleFavoriteItems() {
  const toggleSwitch = document.getElementById('toggleFavorite');

  if (toggleSwitch.checked) {
    displayFavoriteProducts();
  } else {
    search();
  }
}

async function displayFavoriteProducts() {
  const searchResults = document.getElementById('searchResults');
  searchResults.innerHTML = '';
  
  const userToken = getUserToken();
  if (!userToken) {
    searchResults.textContent = 'No favorite items found.';
    return;
  }
  
  try {
    const response = await fetch(`${basePath}favorites_manager.php?action=list`, {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      credentials: 'include',
      body: JSON.stringify({ user_token: userToken })
    });
    const result = await response.json();
    
    if (result.success) {
      const favoriteProducts = result.favorites;
      
      if (favoriteProducts.length === 0) {
        searchResults.textContent = 'No favorite items found.';
      } else {
        favoriteProducts.forEach(product => {
          const itemContainer = createItemContainer(product);
          searchResults.appendChild(itemContainer);
        });
      }
    } else {
      searchResults.textContent = 'Error loading favorites.';
    }
  } catch (error) {
    searchResults.textContent = 'Error loading favorites.';
  }
}

const toggleSwitch = document.getElementById('toggleFavorite');
toggleSwitch.addEventListener('change', toggleFavoriteItems);
if (toggleSwitch.checked) {
  displayFavoriteProducts();
} else {
  search();
}
