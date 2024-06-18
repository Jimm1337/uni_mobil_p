<template>
  <div class="places-container">
    <h2>Odwiedzone miejsca</h2>
    <div v-for="(data, index) in combinedData" :key="index" class="place-container">
      <h3>Miejsce: {{ data.placeName }}</h3>
      <p>Data wizyty: {{ data.timestmp }}</p>
      <button @click="toggleComments(index)" class="toggle-comments-btn">
        {{ data.showComments ? "Ukryj komentarze" : "Pokaż komentarze" }}
      </button>
      <ul v-show="data.showComments" class="comments-list">
        <li v-for="(comment, cIndex) in data.comments" :key="cIndex">
          <div class="comment-content">
            <small>Autor: {{ comment.username }}</small>
            <p>{{ comment.content }}</p>
            <small>Data: {{ comment.timestmp }}</small>
          </div>
        </li>
      </ul>
      <div class="add-comment-container">
        <label for="newCommentInput{{ index }}" class="sr-only">Dodaj komentarz:</label>
        <input
          type="text"
          v-model="newComment[index]"
          :id="'newCommentInput' + index"
          placeholder="Dodaj komentarz"
          class="add-comment-input"
        />
        <button @click="addComment(data.placeid, newComment[index], index)" class="add-comment-btn">
          Dodaj komentarz
        </button>
      </div>
    </div>
  </div>
</template>

<script>
/*eslint-disable*/
import axios from "@/axios";
export default {
  data() {
    return {
      visits: [],
      places: [],
      combinedData: [],
      newComment: [],
      comments: [],
      users: [],
    };
  },
  methods: {
    combineData() {
      this.combinedData = this.visits.map((visit) => {
        const place = this.places.find((p) => p.id === visit.placeid);
        return {
          ...visit,
          placeName: place ? place.name : "Nieznane miejsce",
          placeDescription: place ? place.description : "Brak opisu",
          placeLocation: place ? place.location : "Lokalizacja nieznana",
        };
      });
    },
    fetchVisits() {
      const userID = parseInt(sessionStorage.getItem("userID"));
      if (!userID) {
        console.log(userID);
        console.error("User ID is missing [fetchVisits()]");
        return;
      }
      axios
        .get(`/visits/user/${userID}`, {
          params: {
            start: 0,
            end: 1000,
          },
          headers: {
            Accept: "application/json",
            Authorization: `Basic ${sessionStorage.getItem("auth")}`,
          },
        })
        .then((response) => {
          this.visits = response.data;
          this.combineData();
        })
        .catch((error) => {
          console.error("Error [fetchVisits()]:", error);
          console.log("Error response [fetchVisits()]:", error.response);
        });
    },

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
          this.combineData();
        })
        .catch((error) => {
          console.error("Error [fetchPlaces()]:", error);
          window.location.reload();
        });
    },
    toggleComments(index) {
      const place = this.combinedData[index];
      if (!place.showComments) {
        axios
          .get(`/comments/${place.placeid}?start=0&end=1000`, {
            headers: {
              Accept: "application/json",
              Authorization: `Basic ${sessionStorage.getItem("auth")}`,
            },
          })
          .then((response) => {
            const enrichedComments = response.data.map((comment) => {
              const user = this.users.find((user) => user.id === comment.userid);
              console.log("User found:", user);
              console.log("Comment with user:", {
                ...comment,
                username: user ? user.username : "Nieznany użytkownik",
              });
              return {
                ...comment,
                username: user ? user.username : "Nieznany użytkownik",
              };
            });
            this.combinedData[index].comments = enrichedComments;
            this.combinedData[index].showComments = true;
          })
          .catch((error) => {
            console.error("Error fetching comments:", error);
          });
      } else {
        this.combinedData[index].showComments = false;
      }
    },
    fetchUsers() {
      axios
        .get("/users", {
          headers: {
            Accept: "application/json",
            Authorization: `Basic ${sessionStorage.getItem("auth")}`,
          },
        })
        .then((response) => {
          this.users = response.data;
        })
        .catch((error) => {
          window.location.reload();
          console.error("Error [fetchUsers()]:", error);
        });
    },
    addComment(placeId, content, index) {
      if (!content) return;
      axios
        .post(
          "/comments",
          {
            PlaceID: placeId,
            Content: content,
          },
          {
            headers: {
              Accept: "application/json",
              Authorization: `Basic ${sessionStorage.getItem("auth")}`,
            },
          }
        )
        .then((response) => {
          this.newComment[index] = "";
        })
        .catch((error) => {
          console.error("Error [addComment()]:", error);
        });
    },
  },
  mounted() {
    this.fetchVisits();
    this.fetchPlaces();
    this.fetchUsers();
  },
};
</script>

<style scoped>
.places-container {
  max-width: 800px;
  margin: auto;
}
.edit-comment-btn,
.save-comment-btn {
  background-color: #007bff;
  color: white;
  border: none;
  padding: 8px 12px;
  border-radius: 5px;
  cursor: pointer;
  margin-left: 5px;
}

.save-comment-btn {
  background-color: green;
}

.edit-comment-btn:hover,
.save-comment-btn:hover {
  background-color: #0056b3;
}
.place-container {
  margin-bottom: 20px;
  border: 1px solid #ccc;
  border-radius: 5px;
  padding: 10px;
  text-align: left;
}

.place-container h3 {
  margin-top: 0;
}

.toggle-comments-btn,
.edit-comment-btn,
.add-comment-btn {
  background-color: #007bff;
  color: white;
  border: none;
  padding: 8px 12px;
  border-radius: 5px;
  cursor: pointer;
  margin-right: 10px;
}

.toggle-comments-btn:hover,
.edit-comment-btn:hover,
.add-comment-btn:hover {
  background-color: #0056b3;
}

.add-comment-container {
  margin-top: 10px;
}

.add-comment-input {
  padding: 8px;
  border: 1px solid #ccc;
  border-radius: 5px;
  margin-right: 10px;
}

.edit-comment-input {
  padding: 8px;
  border: 1px solid #ccc;
  border-radius: 5px;
}

.comments-list {
  list-style-type: none;
  padding: 0;
  margin: 0;
}

.sr-only {
  position: absolute;
  width: 1px;
  height: 1px;
  margin: -1px;
  padding: 0;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  border: 0;
}

.comment-content {
  border: 1px solid #ccc;
  padding: 5px;
  border-radius: 5px;
}
</style>
