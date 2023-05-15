<template>
  <!-- App.vue -->
  <v-app>
    <!---------------------------------------------------------------------------------->
    <!-- App Bar -->
    <v-app-bar
      app
      outlined
      clipped-left
      elevation="10"
      height="72"
      
    >
      <!-- Navegation Icon-->
      <v-app-bar-nav-icon color="indigo" @click.stop="drawer = !drawer"></v-app-bar-nav-icon>
      <!-- Tittle of the toolbar -->
      <v-toolbar-title>Menu</v-toolbar-title>
      <!-- Tag to add some space beetween the "Menu" and the Logo-->
      <v-spacer></v-spacer>
      <!-- Tag to add image, here we add the Altao Logo -->
      <v-img
        max-width="150"
        class="mx-8"
        src="@/assets/img/lamotriz.png"
      >
      </v-img>
    </v-app-bar>
    <!---------------------------------------------------------------------------------->
    <!-- Drawer -->
    <v-navigation-drawer
      app
      temporary
      color="blue"
      v-model="drawer"
    >
      <v-list
        nav
        flat
        v-model="selectedItem"
          color="#FFFFFF"
      >
          <v-list-item
            v-for="(item, i) in items"
            :key="i"
            @click="item.redirect"
          >
            <template v-slot:prepend>
              <v-icon :icon="item.icon"></v-icon>
            </template>
            
            <v-list-item-title v-text="item.text"></v-list-item-title>
          </v-list-item>
      </v-list>

    </v-navigation-drawer>
    <!---------------------------------------------------------------------------------->
    <!-- Sizes your content based upon application components -->
    <v-main>
      <!-- Provides the application the proper gutter -->
      <v-container fluid>
        <!-- Using Router -->
        <router-view></router-view>
      </v-container>
    </v-main>
    <!---------------------------------------------------------------------------------->
    <!-- Footer -->
    <v-footer app>
      <!-- -->
    </v-footer>
  </v-app>
</template>

<script>

export default {

  data(){
    return {
      drawer: null,
      selectedItem: 0,
      items:[
        {text: 'Home', icon: 'mdi-home', redirect: () => {this.$router.push('/')}},
        {text: 'Esp32', icon: 'mdi-wifi', redirect: () => {this.$router.push('/esp32')}},
      ]
    }
  }
}
</script>

<style>
</style>