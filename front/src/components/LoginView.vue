<template>
  <div>
    <form class="login-form" @submit.prevent="login">
      <div class="logo">
        <h1>Placesandevents</h1>
      </div>
      <div class="form-group">
        <label for="username">Login:</label>
        <input v-model="username" id="username" type="text" class="form-control" />
      </div>
      <div class="form-group">
        <label for="password">Hasło:</label>
        <input v-model="password" id="password" type="password" class="form-control" />
      </div>
      <button class="btn btn-primary" type="submit">Zaloguj się</button>
      <p class="register-text">Pierwszy raz we Wrocławiu?</p>
      <router-link to="/register" class="btn btn-register">Zarejestruj się</router-link>
    </form>
  </div>
</template>

<script>
/* eslint-disable */
import axios from "@/axios";
export default {
  name: "LoginView",
  data() {
    return {
      username: "",
      password: "",
    };
  },
  methods: {
    async login() {
      const auth = btoa(this.username + ":" + this.password);
      try {
        const response = await axios.post(
          "/login",
          {},
          {
            headers: { Authorization: `Basic ${auth}` },
          }
        );
        sessionStorage.setItem("auth", auth);
        sessionStorage.setItem("userID", response.data.id);
        this.$router.push({ name: "about" });
      } catch (error) {
        alert("Nieprawidłowy login lub hasło");
      }
    },
  },
};
</script>

<style scoped>
.login-form {
  max-width: 350px;
  margin: 0 auto;
  padding: 20px;
  border: 1px solid #eaeaea;
  border-radius: 8px;
  background-color: #f9f9f9;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.user-table {
  width: 100%;
  margin-top: 20px;
  border-collapse: collapse;
  border: 1px solid #eaeaea;
  border-radius: 8px;
  background-color: #f9f9f9;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.form-group {
  margin-bottom: 20px;
}

label {
  display: block;
  font-weight: bold;
  margin-bottom: 5px;
}

.input-group {
  display: flex;
  flex-direction: column;
  align-items: center;
}

input[type="text"],
input[type="password"] {
  width: calc(100% - 24px);
  padding: 12px;
  font-size: 16px;
  border: 1px solid #ccc;
  border-radius: 5px;
  background-color: #fff;
  transition: border-color 0.3s ease;
  box-sizing: border-box;
}

input[type="text"]:focus,
input[type="password"]:focus {
  border-color: #007bff;
}

.btn-group {
  display: flex;
  justify-content: center;
}

.btn {
  width: 80%;
  padding: 12px;
  font-size: 16px;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease;
  margin-bottom: 10px;
}

.btn-primary {
  background-color: #007bff;
  color: #fff;
}

.btn-register {
  width: 60%;
  background-color: #007bff;
  color: #fff;
  text-decoration: none;
}

.register-wrapper {
  text-align: center;
}

.register-text {
  font-size: 16px;
  color: #555;
  font-family: Arial, sans-serif;
  text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.3);
  margin-top: 10px;
}
</style>
