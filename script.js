document.querySelectorAll('ul li a').forEach((link) => {
    function scrollTo(e) {
      e.preventDefault;
      const id = e.target.getAttribute('href');
      document.querySelector(`${id}`).scrollIntoView();
    }
    link.addEventListener('click', scrollTo);
  })
  