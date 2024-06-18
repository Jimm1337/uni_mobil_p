<template>
  <div>
    <h2>Lista miejsc</h2>
    <div class="input-container">
      <label for="code">Kod miejsca: </label>
      <input type="text" v-model="code" id="code" placeholder="Wpisz kod miejsca" />
      <button @click="submitCode">Dodaj</button>
    </div>
    <ul>
      <li v-for="place in places" :key="place.id">
        <div>
          <strong>{{ place.name }}</strong>
          <p>{{ place.description }}</p>
          <p>{{ place.location }}</p>
        </div>
      </li>
    </ul>
  </div>
</template>

<script>
/* eslint-disable */
import axios from "@/axios";
export default {
  data() {
    return {
      places: [],
      code: "",
      favorites: [],
    };
  },
  methods: {
    fetchPlaces() {
      axios
        .get("/places", {
          headers: {
            Accept: "application/json",
            Authorization: `Basic ${sessionStorage.getItem("auth")}`,
          },
        })
        .then((response) => {
          this.places = response.data;
        })
        .catch((error) => {
          window.location.reload();
        });
    },
    submitCode() {
      axios
        .post(
          `/visits?key=${this.code}`,
          {},
          {
            headers: {
              Accept: "application/json",
              Authorization: `Basic ${sessionStorage.getItem("auth")}`,
            },
          }
        )
        .then((response) => {
          alert("Wizyta zarejestrowana!");
        })
        .catch((error) => {
          alert("Błąd przy rejestracji wizyty!");
        });
    },
  },
  mounted() {
    this.fetchPlaces();
  },
};
</script>

<style scoped>
ul {
  list-style-type: none;
  padding: 20px;
  margin: 30px auto 0 auto;
  max-width: 900px;
  border: 2px solid #007bff;
  border-radius: 10px;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
  height: 1000px;
  overflow-y: auto;
}

li {
  margin-bottom: 20px;
  text-align: left;
  padding: 15px;
  border: 1px solid #ccc;
  border-radius: 5px;
}

button {
  background-color: #007bff;
  color: white;
  border: none;
  padding: 12px 24px;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease;
  margin-left: 10px;
}

button:hover {
  background-color: #0056b3;
}

.input-container {
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-bottom: 20px;
  flex-wrap: nowrap;
  width: fit-content;
  margin: 0 auto;
}

.label-container {
  display: flex;
}

.label-container label {
  margin-right: 10px;
}

input[type="text"] {
  padding: 12px;
  border: 1px solid #ccc;
  border-radius: 5px;
  font-size: 16px;
  transition: border-color 0.3s ease;
}

input[type="text"]:focus {
  outline: none;
  border-color: #007bff;
}

.input-container {
  width: fit-content;
  margin: 0 auto;
}
</style>
