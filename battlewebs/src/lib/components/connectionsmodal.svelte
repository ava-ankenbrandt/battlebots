<script lang='ts'>
	import Settingsmodalcheckbox from "./settingsmodalcheckbox.svelte";
  import { reverse_A, reverse_B, reverse_L, reverse_R, switch_L_R_defs, reverse_S1, reverse_S2 } from "$lib/javascript/settingsStores";
    export let connectionsOpen: boolean;
</script>

<div class="modal" class:modal-open={connectionsOpen}>
    <div class="modal-box relative max-w-[90%] w-full">
      <h1 class="font-bold text-2xl text-center">Connections</h1>
      <br>
      <p>This page is temporary! Things to remember: outputs are ABLR left to right; power port is next to the LED with red closer to the LED :)</p>
      <Settingsmodalcheckbox title="Reverse Left Motor" bind:checked={$reverse_L}/>
      <Settingsmodalcheckbox title="Reverse Right Motor" bind:checked={$reverse_R}/>
      <Settingsmodalcheckbox title="Reverse A Motor" bind:checked={$reverse_A}/>
      <Settingsmodalcheckbox title="Reverse B Motor" bind:checked={$reverse_B}/>
      <Settingsmodalcheckbox title="Swap Left/Right Motor Outputs (for when right is plugged into left)" bind:checked={$switch_L_R_defs}/>
      <Settingsmodalcheckbox title="Reverse Servo 1 Idle Position" bind:checked={$reverse_S1}/>
      <Settingsmodalcheckbox title="Reverse Servo 2 Idle Position" bind:checked={$reverse_S2}/>

      
      <div class="modal-action">
        <button class="btn btn-md absolute left-2 top-2" on:click={()=>connectionsOpen = false}>Back</button>
      </div>
    </div>
  </div>