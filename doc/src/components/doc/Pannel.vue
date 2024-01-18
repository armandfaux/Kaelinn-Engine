<!-- BasePage.vue -->
<template>
    <section class="zoom-effect" :style="{ height: height, width: width, backgroundColor: colors, display: 'flex', justifyContent: 'center', alignItems: 'center', borderRadius: '3px', transition: 'transform 0.3s' }">
      <div class="pannel-text" >
          <div>
            <h1 style="font-weight: bolder;"> {{ title }}</h1>
            <p style="font-weight: lighter; font-style: italic;"> {{ location }} </p>
          </div>
          <div>
            <p> {{ firstElements }}</p>
            <p>{{ secondElements}}</p>
         </div>
      </div>
    </section>
  </template>
  
    <script>
      export default {
        name: 'Pannel',
        props: {
          title: String,
          location: String,
          firstElements: String,
          secondElements: String,
          height: {
            type: String,
            default: '30%',
          },
          width: {
            type: String,
            default: '20%',
          },
          colors: {
            type: String,
            default: 'white',
          },
        },
      };
    </script>

    <style scoped>

    .zoom-effect:hover {
      transform: scale(1.05); /* Increase or decrease the value based on the desired zoom effect */
    }

    .pannel-text {
      display: flex;
      flex-direction: column;
      justify-content: space-around;
      height: 95%;
      width: 95%;
    }

  </style>
