<template>
  <div class="container mt-4">
    <h2>Nowe miejsce do odkrycia</h2>
    <form @submit.prevent="submitPlace">
      <div class="form-group">
        <label for="placeName">Nazwa miejsca:</label>
        <input type="text" class="form-control" id="placeName" v-model="place.Name" required />
      </div>
      <div class="form-group">
        <label for="placeDescription"> Opis miejsca: </label>
        <textarea class="form-control" id="placeDescription" v-model="place.Description" required>
        </textarea>
      </div>
      <div class="form-group">
        <label for="placeLocation"> Lokalizacja: </label>
        <input
          type="text"
          class="form-control"
          id="placeLocation"
          v-model="place.Location"
          required
        />
      </div>
      <div class="form-group">
        <label for="placeKey">Klucz:</label>
        <input type="text" class="form-control" id="placeKey" v-model="place.Key" required />
      </div>
      <button type="submit" class="btn btn-primary">Dodaj miejsce</button>
    </form>
  </div>
</template>

<script>
/* eslint-disable */
import axios from "@/axios";
export default {
  data() {
    return {
      place: {
        Name: "",
        Description: "",
        Location: "",
        Key: "",
      },
    };
  },
  methods: {
    submitPlace() {
      axios
        .put("/places", this.place, {
          headers: {
            "Content-Type": "application/json",
            Accept: "application/json",
            Authorization: `Basic ${sessionStorage.getItem("auth")}`,
          },
        })
        .then((response) => {
          alert("Miejsce zostało dodane!");
          console.log(response.data);
        })
        .catch((error) => {
          console.error("Wystąpił błąd:", error);
          alert("Nie udało się dodać miejsca.");
        });
    },
  },
};
</script>

<style>
.custom-form {
  max-width: 500px;
  margin: auto;
  padding: 20px;
  background-color: #f4f4f4;
  border-radius: 10px;
  box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
}

.form-group {
  margin-bottom: 20px;
}

label {
  display: block;
  margin-bottom: 5px;
  font-weight: bold;
}

input[type="text"],
textarea {
  width: 100%;
  padding: 10px;
  border: 1px solid #ccc;
  border-radius: 5px;
}
input[type="text"],
textarea,
button {
  max-width: 400px;
  margin-left: auto;
  margin-right: auto;
}
button {
  display: block;
  width: 200px;
  padding: 10px;
  background-color: #007bff;
  color: #fff;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s ease;
}

button:hover {
  background-color: #0056b3;
}
</style>
