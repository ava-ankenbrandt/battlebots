<script lang='ts'>
	import Settingsmodalitem from "./settingsmodalitem.svelte";
  import { joystick_mode, joystick_modes, a_b_mode, a_b_modes, servo_mode, servo_modes, a_b_reverse, a_b_reverse_modes } from "$lib/javascript/settingsStores";
  export let settingsOpen: boolean;
  export let hornOpen: boolean;

  let reverse_enabled: string[];

  $:{
    if ($a_b_mode === "toggle") {
      reverse_enabled = ["none"];
      $a_b_reverse = "none";
    }else{
      reverse_enabled = a_b_reverse_modes;
    }
  } 
  
</script>

<div class="modal" class:modal-open={settingsOpen}>
    <div class="modal-box relative max-w-[90%] w-full">
      <h1 class="font-bold text-2xl text-center">Settings</h1>
      <br>
      
      <Settingsmodalitem title="Control Mode" options={joystick_modes} bind:selected={$joystick_mode}/>

      <Settingsmodalitem title="A and B Mode" options={a_b_modes} bind:selected={$a_b_mode}/>

      <Settingsmodalitem title="A and B Reverse" options={a_b_reverse_modes} bind:selected={$a_b_reverse} enabled={reverse_enabled}/>
      
      <Settingsmodalitem title="Servo Mode" options={servo_modes} bind:selected={$servo_mode}/>
      
      <br>
      <button class="btn" on:click={() => {settingsOpen = false; hornOpen = true;}}>Configure Horn</button>
      <br><br><br>
      <button class="btn btn-accent">Reset All Settings</button>
      <div class="modal-action">
        <button class="btn btn-md absolute left-2 top-2" on:click={()=>settingsOpen = false}>Back</button>
      </div>
    </div>
  </div>