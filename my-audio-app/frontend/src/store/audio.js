// src/store/audio.js
export default {
  state: {
    audioList: [],
    selectedAudio: null,
  },
  mutations: {
    setAudioList(state, audioList) {
      state.audioList = audioList;
    },
    setSelectedAudio(state, audio) {
      state.selectedAudio = audio;
    },
  },
  actions: {
    async fetchAudioList({ commit }) {
      // Fetch from backend (mocked data)
      commit('setAudioList', [
        { id: 1, name: 'Sample Audio' },
      ]);
    },
    async fetchAudioDetails({ commit }, audioId) {
      // Fetch audio details based on ID (mocked data)
      commit('setSelectedAudio', {
        id: audioId,
        name: 'Sample Audio',
        timeline: [0, 20, 40, 60, 80],
      });
    },
  },
};
