<script lang='ts'>
	import Settingsmodalitem from "./settingsmodalitem.svelte";

    let settings = {joystickMode: false, otherSetting: true};

    export let settingsOpen: boolean;
</script>

<div class="modal" class:modal-open={settingsOpen}>
    <div class="modal-box relative max-w-[90%] w-full">
      <h1 class="font-bold text-2xl text-center">Settings</h1>
      
      <Settingsmodalitem title="Control Mode" options={["Buttons", "Joystick"]}/>

      <Settingsmodalitem title="A and B Mode" options={["Toggle", "Hold"]}/>

      <Settingsmodalitem title="A and B Reverse" options={["None", "A reverses B", "X/Y reverses A/B"]}/>
      
      <br>
      <button class="btn">Configure Horn</button>
      <br><br><br>
      <button class="btn btn-accent">Reset All Settings</button>
      <div class="modal-action">
        <button class="btn btn-md rounded-full absolute left-2 top-2" on:click={()=>settingsOpen = false}>Back</button>
      </div>
    </div>
  </div>