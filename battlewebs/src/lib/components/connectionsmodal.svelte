<script lang='ts'>
	import Settingsmodalcheckbox from "./settingsmodalcheckbox.svelte";
  import { reverse_A, reverse_B, reverse_L, reverse_R, switch_L_R_defs, reverse_SA, reverse_SB } from "$lib/javascript/settingsStores";
    export let connectionsOpen: boolean;
</script>

<div class="modal" class:modal-open={connectionsOpen}>
    <div class="modal-box relative max-w-[90%] w-full">
      <h1 class="font-bold text-2xl text-center">Connections</h1>
      <br>
      
      <Settingsmodalcheckbox title="Reverse Left Motor" bind:checked={$reverse_L}/>
      <Settingsmodalcheckbox title="Reverse Right Motor" bind:checked={$reverse_R}/>
      <Settingsmodalcheckbox title="Reverse A Motor" bind:checked={$reverse_A}/>
      <Settingsmodalcheckbox title="Reverse B Motor" bind:checked={$reverse_B}/>
      <Settingsmodalcheckbox title="Swap Left/Right Motor Outputs (for when right is plugged into left)" bind:checked={$switch_L_R_defs}/>
      <Settingsmodalcheckbox title="Reverse Servo A Idle Position" bind:checked={$reverse_SA}/>
      <Settingsmodalcheckbox title="Reverse Servo B Idle Position" bind:checked={$reverse_SB}/>

      
      <div class="modal-action">
        <button class="btn btn-md absolute left-2 top-2" on:click={()=>connectionsOpen = false}>Back</button>
      </div>
    </div>
  </div>