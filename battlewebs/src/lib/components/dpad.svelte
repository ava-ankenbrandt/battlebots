<script lang='ts'>
    import { ButtonTracker } from "$lib/javascript/buttonTracker";

    function handleClick() { 
        alert('clicked!!!!');
    }

    let u_tracker = new ButtonTracker("up")
    let d_tracker = new ButtonTracker("down")
    let l_tracker = new ButtonTracker("left")
    let r_tracker = new ButtonTracker("right")

</script>

<div class="relative h-full aspect-square bg-base-100 place-items-center max-w-[600px] select-none">
    <svg class="absolute left-0 right-0 top-0 w-full stroke-base-100 stroke-1 fill-primary" viewBox="0 0 50 50" id="canvas">
        <polygon points="0,0 50,0 25.0,25.0"></polygon>
        <polygon points="0,0 0,50 25.0,25.0"></polygon>
        <polygon points="50,50 50,0 25.0,25.0"></polygon>
        <polygon points="50,50 0,50 25.0,25.0"></polygon>
    </svg>
    <svg class="absolute left-0 right-0 top-0 w-full fill-primary-content" viewBox="0 0 50 50" id="canvas2">
        <polygon points="10,20 10,30 6,25"></polygon>
        <polygon points="20,10 30,10 25,6"></polygon>
        <polygon points="40,20 40,30 44,25"></polygon>
        <polygon points="20,40 30,40 25,44"></polygon>
    </svg>
    <svg class="absolute left-0 right-0 top-0 w-full fill-primary-content stroke-1 stroke-base-100" viewBox="0 0 50 50" id="canvas2">
        <polygon on:mousedown={(e) => u_tracker.mousedown(e)} class="fill-transparent active:fill-neutral opacity-30" points="0,0 50,0 25.0,25.0"></polygon>
        <polygon on:mousedown={(e) => l_tracker.mousedown(e)} class="fill-transparent active:fill-neutral opacity-30" points="0,0 0,50 25.0,25.0"></polygon>
        <polygon on:mousedown={(e) => r_tracker.mousedown(e)} class="fill-transparent active:fill-neutral opacity-30" points="50,50 50,0 25.0,25.0"></polygon>
        <polygon on:mousedown={(e) => d_tracker.mousedown(e)} class="fill-transparent active:fill-neutral opacity-30" points="50,50 0,50 25.0,25.0"></polygon>
    </svg>
</div>