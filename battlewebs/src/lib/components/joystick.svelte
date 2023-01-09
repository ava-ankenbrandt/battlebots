<script lang="ts">
	import { onMount } from "svelte";
	import { PwmMessage, websocket_manager } from '$lib/javascript/websocket_manager';

    let isMounted = false;
    let x = 0;
    let y = 0;
    let outerdiv : HTMLElement;
    let isDragging = false;
	let circd = 100;

    onMount(() => {
        x = outerdiv.clientWidth/2 - circd/2;
        y = outerdiv.clientWidth/2 - circd/2;
        isMounted = true;
    })

    function handleMouseMove(event: any) {
        if (isDragging === true) {
            x = event.clientX - circd/2;
            y = event.clientY - circd/2;
            if (x + circd/2 > outerdiv.clientWidth) {
                isDragging = false;
            }
            let x_norm = (event.clientX - outerdiv.clientWidth / 2) / outerdiv.clientWidth * 512;
            let y_norm = (event.clientY - outerdiv.clientWidth / 2) / outerdiv.clientWidth * -512;
            // ^ origin is now bottom left, range of above is +-256 :)
            let L_out = y_norm + x_norm;
            let R_out = y_norm - x_norm;

            // todo: send websocket requests
        }else{
            handleMouseUp()
        }
    }

    function handleMouseDown(event: any) {
        isDragging = true;
        x = event.clientX - circd/2;
        y = event.clientY - circd/2;
    }

    function handleMouseUp() {
        isDragging = false;
        x = outerdiv.clientWidth/2 - circd/2;
        y = outerdiv.clientWidth/2 - circd/2;
        // todo: send websocket request to halt motors
    }
</script>

<div class="relative h-full aspect-square bg-base-100 max-w-[600px]" on:pointerdown={handleMouseDown} on:pointerout={handleMouseUp} on:pointerup={handleMouseUp} on:pointermove={handleMouseMove} bind:this={outerdiv}>
    <div class="relative aspect-square bg-primary rounded-full"></div>
    <div class="w-[24px] h-[24px] rounded-full select-none bg-primary-content absolute" style="left: {x}px; top: {y}px; width:{circd}px; height:{circd}px;" class:bg-transparent={!isMounted}/>
</div>