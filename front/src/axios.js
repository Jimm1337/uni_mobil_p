import axios from 'axios';

const instance = axios.create({
  baseURL: 'http://185.238.75.123:8000',
});

export default instance;
