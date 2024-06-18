<template>
  <div>
    <nav v-if="!$route.meta.hideMenu">
      <router-link to="/about">Miejsca</router-link>
      <router-link to="/favourite">Ulubione</router-link>
      <router-link to="/ranking">Ranking</router-link>
      <router-link to="/form" v-if="checkToken()">Nowe miejsce</router-link>
      <router-link to="/">Wyloguj</router-link>
    </nav>
    <router-view />
  </div>
</template>

<script>
/* eslint-disable */
export default {
  methods: {
    checkToken() {
      const token = sessionStorage.getItem("auth");
      return token === "YWRtaW4wOmFkbWlu";
    },
  },
};
</script>

<style>
#app {
  font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #333;
  margin-top: 20px;
}

nav {
  display: block;
  background-color: #f2f2f2;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  padding: 10px 30px;
  border-radius: 8px;
  margin-bottom: 20px;
}

nav a {
  text-decoration: none;
  color: #42b983;
  font-size: 20px;
  font-weight: 500;
  margin: 0 15px;
  position: relative;
}

nav a:hover {
  color: #333;
}

nav a::after {
  content: "";
  position: absolute;
  width: 0;
  height: 2px;
  display: block;
  margin-top: 5px;
  right: 0;
  background: #42b983;
  transition: width 0.3s ease;
  -webkit-transition: width 0.3s ease;
}

nav .menu-container {
  padding-right: 40px;
}

nav a:hover::after {
  width: 100%;
  left: 0;
  background: #333;
}

nav a.router-link-exact-active {
  color: #42b983;
  font-weight: bold;
}

nav a.router-link-exact-active::after {
  background: #333;
}
</style>
