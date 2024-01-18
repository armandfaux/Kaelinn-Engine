<template>
  <section class="base-component">
    <div class="one">
      <h1>The GLOBAL ARCHITECTURE</h1>
    </div>
    <!-- Base Instructions -->
    <div style="width: 30%; height: 20%; display: flex; justify-content: center; align-items: center;">
      <div style="width: 50%; height: 60%; display: flex; justify-content: space-around;">
        <div style="display: flex; flex-wrap: wrap; justify-content: space-around;">
          <h1 style=" width: 40%; height: 25%; background-color: #D38AFF; border-radius: 3px; display: flex; justify-content: center; align-items: center;">Client Side</h1>
          <h1 style=" width: 40%; height: 25%; background-color: #BCFFFF; border-radius: 3px; display: flex; justify-content: center; align-items: center;">Component</h1>
          <h1 style=" width: 40%; height: 25%; background-color: #7BE99A; border-radius: 3px; display: flex; justify-content: center; align-items: center;">Server Side</h1>
          <h1 style=" width: 40%; height: 25%; background-color: #ADADAD; border-radius: 3px; display: flex; justify-content: center; align-items: center;">Tools</h1>
        </div>
      </div>
      <div style="width: 44%; height: 100%; display: flex; flex-direction: column; justify-content: space-around; align-items: flex-end;">
        <Pannel title="class Game (App ?)" location="// defines any game made with the engine" firstElements="vector<Scene> _scenes" secondElements="vector <ISystem> _systems" :height="'22vh'" :width="'31vh'"/>
        <Pannel title="class Scene" location="/engine/core" firstElements="vector<Entity> _entities" secondElements="double y;" :height="'22vh'" :width="'31vh'"/>
      </div>
    </div>

    <div style=" height: 85%; width: 95%; display: flex;  justify-content: space-around; flex-direction: column;">
      <!-- Base First Container -->
      <div style="display: flex; justify-content: space-evenly; width: 60%; height: 40%;">

        <!-- Base Left Side Container -->
        <div style="width: 22%; height: 71%; display: flex; background-color: #ADADAD; border-radius: 5px; align-items: flex-start; flex-direction: column;">
          <div style="display: flex; width: 100%;  padding-left: 2%;">
              <h1>MATHS</h1>
          </div>
          <div style="width: 100%; height: 100%; display: flex;">
            <div style="width: 100%; height: 50%; display: flex; justify-content: center; align-items: center;">
              <Pannel title="Vector2" location="// custome vector" firstElements="double x;" secondElements="double y;" :height="'22vh'" :width="'20vw'" />
            </div>
          </div>
        </div>

        <!-- Base Right Side Container -->
        <div style="width: 70%; height: 70%; border-radius: 5px; background-color: #FF9090; display: flex;  align-items: center; flex-direction: column;">
          <div style="display: flex; width: 100%;  padding-left: 2%;">
              <h1>ECS</h1>
          </div>
          <div style="width: 100%; height: 100%; display: flex;">
            <div style="width: 100%; height: 100%; display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center;">
              <Pannel title="interface Entity" location="/engine/interface" firstElements="void addComp()" secondElements="bool hasComp()" :height="'22vh'" :width="'20vw'"/>
              <Pannel title="interface IComponent" location="/engine/interface" firstElements="getId()" secondElements="getName()" :height="'22vh'" :width="'20vw'"/>
              <Pannel title="class Entity" location="/engine/core" firstElements="double _id" secondElements="vector<IComponent> _comps" :height="'22vh'" :width="'20vw'"/>
              <Pannel title="class AComponent" location="/engine/component" firstElements="std::string _name" secondElements="double _id" :height="'22vh'" :width="'20vw'"/>
            </div>
            <div style="width: 40%; height: 100%; display: flex; align-items: center; justify-content: space-around; flex-direction: column;">
              <Pannel title="interface ISystem" location="/engine/interface" firstElements="virtual void update(vector<Entity>)" secondElements="// called once a frame" :height="'22vh'" :width="'20vw'"/>
              <Pannel title="class ASystem" location="/engine/system" firstElements="double _id" secondElements="placeholder" :height="'22vh'" :width="'20vw'"/>
            </div>
          </div>
        </div>
      </div>
    <!-- Base Below Container-->
      <div style="display: flex; justify-content: space-evenly; width: 90%; height: 60%;">
        <!-- Base Left Side Container -->
        <div style="width: 15%; height: 100%; border-radius: 5px; background-color: #ADADAD; display: flex; flex-direction: column;">
          <div style="display: flex; justify-content: ; width: 100%;  padding-left: 2%;">
            <h1>EVENT BUS</h1>
          </div>
          <div style="width: 100%; height: 100%; display: flex; align-items: center; justify-content: space-around; flex-direction: column;">
            <Pannel title="struct Event" location="// a game event" firstElements="type (input | pos)  & std::string input" secondElements="uint32_t entity_id & Vector2 pos" :height="'22vh'" :width="'15vw'"/>
            <Pannel title="Publisher" location="// broadcast events" firstElements="void publish(event&) & void subscribe(ISubscriber)" secondElements="vector<ISubscriber> _subscribers" :height="'22vh'" :width="'15vw'"/>
            <Pannel title="ISubscriber" location="// receive events" firstElements="void onEvent(event&)" secondElements="" :height="'22vh'" :width="'15vw'"/>

          </div>
        </div>

        <!-- Base Right Side Container -->
        <div style="width: 80%; height: 100%; display: flex; justify-content: flex-start; align-items: end;">
          <div style="width: 60%; height: 100%; display: flex; justify-content: flex-end;">
              <div style="width: 32%; height: 100%; display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center;">
                <Pannel title="Spatial" location="// the entity position" firstElements="Vector2 _pos" secondElements="double y;" :height="'22vh'" :width="'20vw'" colors="#BCFFFF"/>
                <Pannel title="Sprite" location="// make the entity drawable" firstElements="string filePath" secondElements="Vector2 _rotation" :height="'22vh'" :width="'20vw'" colors="#BCFFFF"/>
                <Pannel title="Interactive" location="// buttons" firstElements="_event // broadcasted event onclick" secondElements="" :height="'22vh'" :width="'20vw'" colors="#BCFFFF"/>
                <Pannel title="Input" location="// make the entity sensible to user inputs" firstElements="lorem ipsum" secondElements="" :height="'22vh'" :width="'20vw'" colors="#BCFFFF"/>
                <Pannel title="Durability" location="//" firstElements="double _health, _maxHealth & void heal()" secondElements="void injure()" :height="'22vh'" :width="'20vw'" colors="#BCFFFF"/>
              </div>
              <div style="width: 34%; height: 100%; display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center;">
                <Pannel title="RenderSystem" location="// render all the entities" firstElements="_objects // custom graphic objects" secondElements="_window // graphic render window" :height="'22vh'" :width="'20vw'" colors="#D38AFF"/>
                <Pannel title="PhysicSystem" location="// physic calculation" firstElements="update()" secondElements="double y;" :height="'22vh'" :width="'20vw'" colors="#7BE99A"/>
                <Pannel title="Event System" location="// handle all game events" firstElements="description" secondElements="" :height="'22vh'" :width="'20vw'" colors="#D38AFF"/>
                <Pannel title="Event Bus" location="// handle all game events" firstElements="description" secondElements="" :height="'22vh'" :width="'20vw'"/>
                <Pannel title="InputSystem" location="// physic calculation" firstElements="update()" secondElements="" :height="'22vh'" :width="'20vw'" colors="#D38AFF"/>
              </div>
          </div>
          <div style="height: 58.8%;  width: 20%; display: flex; justify-content: center;">
            <div style="width: 100%; height: 77%; display: flex; justify-content: space-between; flex-direction: column; align-items: center;">
              <Pannel title="Network System" location="// bridge between the client and the server" firstElements="update()" secondElements="subscriber.onEvent() {transmit data}" :height="'22vh'" :width="'20vw'" />
              <Pannel title="Network Protocol" location="// client-server communication" firstElements="CONNECT : new client connect to the server CREATE : create a new room" secondElements="JOIN [ID] : join the room with given ID START : start the game for the current lobby  EVENT [EventType] [EventContent]" :height="'35vh'" :width="'20vw'" colors="#ADADAD"/>
            </div>
          </div>
          <div style="height: 100%; width: 20%; display: flex; flex-direction: column; justify-content: space-evenly;">
            <!-- <div style=" height: 100%; width: 100%; display: flex;"> -->
              <div style="width: 100%; height: 49%; display: flex; justify-content: space-evenly; flex-direction: column; align-items: center;">
                <Pannel title="SDL" location="// external graphic library (self-contained)" firstElements="description" secondElements="" :height="'22vh'" :width="'20vw'" colors="#D38AFF"/>
                <Pannel title="SFML" location="// external graphic library (self-contained)" firstElements="description" secondElements="double y;" :height="'22vh'" :width="'20vw'" colors="#D38AFF"/>
              </div>
              <div style="width: 100%; height: 70%; display: flex; justify-content: flex-start; gap: 23px; flex-direction: column; align-items: center;">
                <Pannel title="Server" location="// networking tools" firstElements="host the RType games" secondElements="" :height="'22vh'" :width="'20vw'" colors="#7BE99A"/>
                <Pannel title="Lobby Manager" location="// header" firstElements="// list of connected players for each lobby" secondElements="" :height="'22vh'" :width="'20vw'" colors="#7BE99A"/>
              <!-- </div> -->
            </div>
          </div>
        </div>
      </div>
    </div>
    <!-- <div style="background-color: palevioletred; height: 85%; width: 95%; display: flex; justify-content: flex-end; flex-direction: column;">
      <div style="display: flex; background-color: gold; height: 35%; width: 100%;">

      </div>
    </div> -->
  </section>
</template>

<script>
import Pannel from '../components/doc/Pannel.vue';

export default {
  name: 'App',
  components: {
    Pannel,
  },
};


</script>

<style scoped>

  .one {
    width: 100%;
    height: 5%;
    display: flex;
    justify-content: center;
    align-items: center;
    background-color: whitesmoke;
  }

  .one h1 {
    text-align: center;
    text-transform: uppercase;
    padding-bottom: 5px;
  }

  .one h1:after {
  width: 100px;
  height: 1px;
  display: block;
  content: "";
  position: relative;
  margin-top: 25px;
  left: 50%;
  margin-left: -50px;
  background-color: #b80000;
}

  .base-component {
    display: flex;
    height: 300vh;
    width: 155vw;
    flex-direction: column;
    background-color: #2f855a8f;
  }
</style>