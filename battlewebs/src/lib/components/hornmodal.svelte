<script lang="ts">
    import { HornMessage, websocket_manager } from "$lib/javascript/websocket_manager";
    export let hornOpen: boolean;
    let notes = ['C','D','E','F','G','A','B','C','D','E','F','G','A','B','C'];
    
    function playSound(noteID: number) {
        websocket_manager.send_command(new HornMessage(noteID));
    }

    function stopSound() {
        websocket_manager.send_command(new HornMessage(0));
    }
</script>

<div class="modal" class:modal-open={hornOpen}>
    <div class="modal-box relative max-w-[90%] h-[80%] w-full flex flex-col">
        <h1 class="font-bold text-2xl text-center">Configure Horn</h1>
        <br>
        <div class="grid grid-cols-5 gap-4 flex-grow">
            {#each Array(15) as _, index (index)}
		        <button class='rounded-lg btn-primary select-none' on:pointerdown={() => {playSound(index+1)}} on:pointerup={() => {stopSound()}} on:pointerleave={() => {stopSound()}}>{notes[index]}</button>
	        {/each}
        </div>
        <div class="modal-action">
            <button class="btn btn-md absolute left-2 top-2 select-none" on:click={()=>hornOpen = false}>Back</button>
        </div>
    </div>
</div>