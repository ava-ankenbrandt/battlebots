<script lang="ts">
    import { HornMessage, websocket_manager } from "$lib/javascript/websocket_manager";
    export let hornOpen: boolean;
    let notes = ['C','D','E','F','G','A','B','C','D','E','F','G','A','B','C'];
    
    function stopSound() {
        websocket_manager.send_command(new HornMessage(0));
    }
</script>

<div class="modal" class:modal-open={hornOpen}>
    <div class="modal-box relative max-w-[90%] w-full">
        <h1 class="font-bold text-2xl text-center">Configure Horn</h1>
        <br>
        <div class="grid grid-cols-5 gap-4">
            {#each Array(15) as _, index (index)}
		        <button class='btn btn-primary' on:click={() => {websocket_manager.send_command(new HornMessage(index+1))}} on:pointerup={() => {stopSound()}} on:pointerleave={() => {stopSound()}}>{notes[index]}</button>
	        {/each}
        </div>
        <div class="modal-action">
            <button class="btn btn-md absolute left-2 top-2" on:click={()=>hornOpen = false}>Back</button>
        </div>
    </div>
</div>