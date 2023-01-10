<script lang='ts'>
    import { ButtonTracker } from "$lib/javascript/buttonTracker";
	import { PwmMessage, websocket_manager } from '$lib/javascript/websocket_manager';
    import { reverse_L, reverse_R } from "$lib/javascript/settingsStores";

    let u_tracker = new ButtonTracker("up")
    let d_tracker = new ButtonTracker("down")
    let l_tracker = new ButtonTracker("left")
    let r_tracker = new ButtonTracker("right")

    let L_out = 0;
    let R_out = 0;
    let fwd_max = 255;
    let turn_max = 128;

    $:{
        L_out = ($u_tracker ? fwd_max : 0) + ($l_tracker ? -turn_max : 0) + ($r_tracker ? turn_max : 0) + ($d_tracker ? -fwd_max : 0);
        R_out = ($u_tracker ? fwd_max : 0) + ($l_tracker ? turn_max : 0) + ($r_tracker ? -turn_max : 0) + ($d_tracker ? -fwd_max : 0);

        if ($reverse_L === true) {L_out *= -1;}
        if ($reverse_R === true) {R_out *= -1;}

        websocket_manager.send_command(new PwmMessage(3, L_out))
        websocket_manager.send_command(new PwmMessage(4, R_out))
        // although this logic often results in outputs > 255, it makes total sense when clamped to 255 :D.
        // pushing u+r results in a "forward leaning right" motion where only one motor moves.
        // probably also worth testing: lessen 'spin speed' tied to l and r to make robots easier to control?
        // ^ this would also result in more fun strafing when two buttons are pressed
    }

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
        <polygon on:pointerdown={(e) => u_tracker.mousedown(e)} on:pointerleave={(e) => u_tracker.mouseup(e)} on:pointerup={(e) => u_tracker.mouseup(e)} class="fill-transparent opacity-30" class:fill-neutral={$u_tracker === true} points="0,0 50,0 25.0,25.0"></polygon>
        <polygon on:pointerdown={(e) => l_tracker.mousedown(e)} on:pointerleave={(e) => l_tracker.mouseup(e)} on:pointerup={(e) => l_tracker.mouseup(e)} class="fill-transparent opacity-30" class:fill-neutral={$l_tracker === true} points="0,0 0,50 25.0,25.0"></polygon>
        <polygon on:pointerdown={(e) => r_tracker.mousedown(e)} on:pointerleave={(e) => r_tracker.mouseup(e)} on:pointerup={(e) => r_tracker.mouseup(e)} class="fill-transparent opacity-30" class:fill-neutral={$r_tracker === true} points="50,50 50,0 25.0,25.0"></polygon>
        <polygon on:pointerdown={(e) => d_tracker.mousedown(e)} on:pointerleave={(e) => d_tracker.mouseup(e)} on:pointerup={(e) => d_tracker.mouseup(e)} class="fill-transparent opacity-30" class:fill-neutral={$d_tracker === true} points="50,50 0,50 25.0,25.0"></polygon>
    </svg>
</div>