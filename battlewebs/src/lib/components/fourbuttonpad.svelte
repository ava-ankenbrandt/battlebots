<script lang="ts">
	import { ButtonTracker } from "$lib/javascript/buttonTracker";
	import type { HtmlTag } from "svelte/internal";
	import Fourbuttonpadbutton from "./fourbuttonpadbutton.svelte";

    let x_tracker = new ButtonTracker("X")
    let y_tracker = new ButtonTracker("Y")
    let a_tracker = new ButtonTracker("A")
    let b_tracker = new ButtonTracker("B")

    interface ButtonProps {
        title: string;
        mousedown: any;
        mouseup: any;
    }

    const buttons: ButtonProps[] = [
        {
            title: "X",
            mousedown: (e: any) => x_tracker.mousedown(e),
            mouseup: (e: any) => x_tracker.mouseup(e)
        },
        {
            title: "Y",
            mousedown: (e: any) => y_tracker.mousedown(e),
            mouseup: (e: any) => y_tracker.mouseup(e)
        },
        {
            title: "A",
            mousedown: (e: any) => a_tracker.mousedown(e),
            mouseup: (e: any) => a_tracker.mouseup(e)
        },
        {
            title: "B",
            mousedown: (e: any) => b_tracker.mousedown(e),
            mouseup: (e: any) => b_tracker.mouseup(e)
        }
    ]

    
</script>

<div class="flex-1 flex justify-center items-center align-middle">
        
    <div class="p-0 flex grow h-[100vh]">
        <div class="grid grid-cols-2 gap-2 p-1 w-full h-full">
            {#each buttons as {title, mousedown, mouseup}}
                <Fourbuttonpadbutton on:pointerdown={mousedown} on:pointerup={mouseup} on:pointerleave={mouseup} title={title}></Fourbuttonpadbutton>

            {/each}
        </div>
    </div>

    
</div>