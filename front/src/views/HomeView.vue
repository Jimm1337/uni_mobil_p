<template>
  <div class="home">
    <img alt="Vue logo" src="../assets/logo.png" />
    <LoginView />
  </div>
</template>

<script>
/* eslint-disable */
import LoginView from "@/components/LoginView.vue";

export default {
  name: "HomeView",
  components: {
    LoginView,
  },
};
</script>
