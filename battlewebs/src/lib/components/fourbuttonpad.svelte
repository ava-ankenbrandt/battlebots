<script lang="ts">
	import { ButtonTracker } from "$lib/javascript/buttonTracker";
	import type { HtmlTag } from "svelte/internal";
	import Fourbuttonpadbutton from "./fourbuttonpadbutton.svelte";

    import { reverse_A, reverse_B, a_b_mode, a_b_reverse, servo_mode } from "$lib/javascript/settingsStores";
    // please remember that capital A and B are outputs and lowercase a and b are buttons

	import { PwmMessage, websocket_manager } from '$lib/javascript/websocket_manager';

    let x_tracker = new ButtonTracker("X")
    let y_tracker = new ButtonTracker("Y")
    let a_tracker = new ButtonTracker("A")
    let b_tracker = new ButtonTracker("B")

    interface ButtonProps {
        title: string;
        tracker: ButtonTracker;
        mousedown: any;
        mouseup: any;
    }

    interface OutputValues {
        A_out: number;
        B_out: number;
        X_out: number; // x_out and y_out are fake, they don't go anywhere, they're just used for button graphics lol
        Y_out: number;
    }

    const buttons: ButtonProps[] = [
        {
            title: "X",
            tracker: x_tracker,
            mousedown: (e: any) => x_tracker.mousedown(e),
            mouseup: (e: any) => x_tracker.mouseup(e)
        },
        {
            title: "Y",
            tracker: y_tracker,
            mousedown: (e: any) => y_tracker.mousedown(e),
            mouseup: (e: any) => y_tracker.mouseup(e)
        },
        {
            title: "A",
            tracker: a_tracker,
            mousedown: (e: any) => a_tracker.mousedown(e),
            mouseup: (e: any) => a_tracker.mouseup(e)
        },
        {
            title: "B",
            tracker: b_tracker,
            mousedown: (e: any) => b_tracker.mousedown(e),
            mouseup: (e: any) => b_tracker.mouseup(e)
        }
    ]

    let output_values: OutputValues = {A_out: 0, B_out: 0, X_out: 0, Y_out: 0};

    let last_A_state = false;
    let last_B_state = false;

    $:{

        let revA = $reverse_A ? -1 : 0;
        let revB = $reverse_B ? -1 : 0;

        if ($a_b_mode === "toggle") { // default mode. Assumes you'll want to turn a motor on and leave it on.

            if ($a_b_reverse === "none") {
                if ($a_tracker === true) {
                    last_A_state = !last_A_state;
                    output_values.A_out = (last_A_state ? 255 : 0) * revA;
                }
                if ($b_tracker === true) {
                    last_B_state = !last_B_state
                    output_values.B_out = (last_B_state ? 255 : 0) * revB;
                }
            }

        }else{ // hold mode. Hold down button to move motor. Useful for strong motors, especially in conjunction with "a reverse b" or "xy reverse ab" modes
            if ($a_b_reverse === "none") { // no reverse behaviour. Holding a turns A, holding b turns B.
                output_values.A_out = ($a_tracker ? 255 : 0) * revA;
                output_values.B_out = ($b_tracker ? 255 : 0) * revB;
            }else if ($a_b_reverse === "a reverses b") { // reverse behaviour. Holding a turns A and turns B in reverse. Holding b turns B and turns A in reverse.
                output_values.A_out = (($a_tracker ? 255 : 0) + ($b_tracker ? -255 : 0)) * revA;
                output_values.B_out = (($b_tracker ? 255 : 0) + ($a_tracker ? -255 : 0)) * revB;
            }else{ // gigareverse. Holding a turns A; b turns B. Holding x turns A in reverse. Holding y turns B in reverse.
                output_values.A_out = (($a_tracker ? 255 : 0) + ($x_tracker ? -255 : 0)) * revA;
                output_values.B_out = (($b_tracker ? 255 : 0) + ($y_tracker ? -255 : 0)) * revB;
                // TODO: disable horn and servos in this case.
            }
        }
        console.log("--")
        console.log(output_values);

        output_values.X_out = $x_tracker ? 255 : 0;
        output_values.Y_out = $y_tracker ? 255 : 0; // TODO: fix errors with multitouch on these buttons in hold->xy/ab reverse mode
        // for some reason in that case specifically the buttons are mutually exclusive?

        websocket_manager.send_command(new PwmMessage(1, output_values.A_out))
        websocket_manager.send_command(new PwmMessage(2, output_values.B_out))

    }
    
</script>

<div class="flex-1 flex justify-center items-center align-middle select-none">
        
    <div class="p-0 flex grow h-[100vh]">
        <div class="grid grid-cols-2 gap-2 p-1 w-full h-full">
            {#each buttons as {title, tracker, mousedown, mouseup}}
                <Fourbuttonpadbutton on:pointerdown={mousedown} on:pointerup={mouseup} on:pointerleave={mouseup} title={title} active={
                    Object.entries(output_values).find(( [k,v] ) => { return k.includes(title) && v > 0 }) != undefined
                }></Fourbuttonpadbutton>

            {/each}
        </div>
    </div>

    
</div>