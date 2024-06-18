<template>
  <div>
    <img alt="Vue logo" src="../assets/logo.png" />
    <form class="register-form" @submit.prevent="register">
      <div class="logo">
        <h1>Placesandevents</h1>
      </div>
      <div class="form-group">
        <label for="register-username">Nazwa użytkownika:</label>
        <input v-model="Username" id="register-username" type="text" class="form-control" />
      </div>
      <div class="form-group">
        <label for="register-login">Login:</label>
        <input v-model="Login" id="register-login" type="text" class="form-control" />
      </div>
      <div class="form-group">
        <label for="register-password">Hasło:</label>
        <input v-model="Password" id="register-password" type="password" class="form-control" />
      </div>
      <div class="form-group">
        <label for="confirm-password">Powtórz hasło:</label>
        <input
          v-model="ConfirmPassword"
          id="confirm-password"
          type="password"
          class="form-control"
        />
      </div>
      <button class="login-button" type="submit">Zarejestruj się</button>
      <div class="spacer"></div>
      <a href="/" class="back-button">Powrót</a>
    </form>
  </div>
</template>

<script>
/* eslint-disable */
import axios from "@/axios";

export default {
  name: "RegisterView",
  data() {
    return {
      Username: "",
      Login: "",
      Password: "",
      ConfirmPassword: "",
    };
  },
  methods: {
    register() {
      if (this.Password !== this.ConfirmPassword) {
        alert("Hasła nie są takie same");
      } else {
        axios
          .post("/register", {
            Username: this.Username,
            Login: this.Login,
            Password: this.Password,
          })
          .then((response) => {
            alert("Rejestracja zakończona sukcesem");
            this.$router.push({ name: "home" });
          })
          .catch((error) => {
            alert("Rejestracja zakończona niepowodzeniem");
          });
      }
    },
  },
};
</script>

<style scoped>
.register-form {
  max-width: 350px;
  margin: 0 auto;
  padding: 20px;
  border: 1px solid #eaeaea;
  border-radius: 8px;
  background-color: #f9f9f9;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  display: flex;
  flex-direction: column;
}

.form-group {
  margin-bottom: 20px;
}

label {
  display: block;
  font-weight: bold;
  margin-bottom: 5px;
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

button.login-button,
a.back-button {
  display: block;
  width: 80%;
  padding: 12px;
  font-size: 16px;
  background-color: #007bff;
  color: #fff;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease;
  align-self: center;
  text-decoration: none;
  text-align: center;
}

button.login-button:hover,
a.back-button:hover {
  background-color: #0056b3;
}

a.back-button {
  width: auto;
  margin-right: auto;
  margin-top: 20px;
}

.spacer {
  height: 20px;
}
</style>
