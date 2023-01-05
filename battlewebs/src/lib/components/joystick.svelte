<script lang="ts">
	import { onMount } from "svelte";
    let isMounted = false;
    let x = 0;
    let y = 0;
    let outerdiv : HTMLElement;
    let isDragging = false;
	let circd = 100;

    onMount(() => {

        x = outerdiv.clientHeight/2 - circd/2;
        y = outerdiv.clientHeight/2 - circd/2;
        isMounted = true;
    })

    function handleMouseMove(event: any) {
        if (isDragging === true) {
            x = event.clientX - circd/2;
            y = event.clientY - circd/2;
            if (x + circd/2 > outerdiv.clientHeight) {
                isDragging = false;
            }
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
        x = outerdiv.clientHeight/2 - circd/2;
        y = outerdiv.clientHeight/2 - circd/2;
    }
</script>

<div class="relative h-full aspect-square bg-base-100 max-w-[600px]" on:pointerdown={handleMouseDown} on:pointerout={handleMouseUp} on:pointerup={handleMouseUp} on:pointermove={handleMouseMove} bind:this={outerdiv}>
    <div class="relative aspect-square bg-primary rounded-full"></div>
    <div class="w-[24px] h-[24px] rounded-full select-none bg-primary-content absolute" style="left: {x}px; top: {y}px; width:{circd}px; height:{circd}px;" class:bg-transparent={!isMounted}/>
</div>