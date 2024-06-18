<template>
  <div class="table-container">
    <h2>Ranking użytkowników</h2>
    <table class="user-table">
      <thead>
        <tr>
          <th>Turysta</th>
          <th>Liczba odwiedzonych miejsc</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="user in users" :key="user.id">
          <td>{{ user.username }}</td>
          <td class="align-right">{{ user.points }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
/* eslint-disable */
import axios from "@/axios";
export default {
  data() {
    return {
      users: [],
      start: 0,
      end: 1000,
    };
  },
  methods: {
    fetchRanking() {
      axios
        .get("/ranking", {
          params: {
            start: this.start,
            end: this.end,
          },
          headers: {
            Accept: "application/json",
            Authorization: `Basic ${sessionStorage.getItem("auth")}`,
          },
        })
        .then((response) => {
          this.users = response.data;
        })
        .catch((error) => {
          console.log("Error response data [fetchRanking()]:", error.response.data);
        });
    },
  },
  mounted() {
    this.fetchRanking();
  },
};
</script>

<style scoped>
.table-container {
  max-width: 700px;
  margin: 0 auto;
}

.user-table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 20px;
  border: 1px solid #eaeaea;
  border-radius: 8px;
  background-color: #f9f9f9;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.user-table th,
.user-table td {
  border: 1px solid #eaeaea;
  padding: 10px;
  text-align: center;
}

.user-table th {
  background-color: #f2f2f2;
  font-weight: bold;
}

.user-table tbody tr:nth-child(even) {
  background-color: #f2f2f2;
}

.user-table tbody tr:hover {
  background-color: #ddd;
}

.align-right {
  text-align: right;
}
</style>
