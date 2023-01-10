<script lang='ts'>
    import { onMount } from 'svelte';
    import Dpad from "$lib/components/dpad.svelte";
    import Settingsmodal from '$lib/components/settingsmodal.svelte';
	import Sidebuttons from '$lib/components/sidebuttons.svelte';
	import Fourbuttonpad from '$lib/components/fourbuttonpad.svelte';
	import Joystick from '$lib/components/joystick.svelte';
	import Connectionsmodal from '$lib/components/connectionsmodal.svelte';
    import { joystick_mode } from '$lib/javascript/settingsStores';
	import { WatchdogMessage, websocket_manager } from '$lib/javascript/websocket_manager';
	import Hornmodal from '$lib/components/hornmodal.svelte';

    let windowWidth: number;
    let windowHeight: number;

    let isFocused = true;

    function rotateAlert() {
        alert('Please use landscape mode!');
    }

    let isSettingsOpen = false;
    let isConnectionsOpen = false;
    let isHornOpen = false;

    onMount(() => {
		if (windowWidth < windowHeight) {
            rotateAlert();
        }
	});

    setInterval(() => {
        if (isFocused === true) {
            websocket_manager.send_command(new WatchdogMessage());
        }
    }, 1000)

</script>

<svelte:window bind:innerWidth={windowWidth} bind:innerHeight={windowHeight} on:blur={() => {isFocused = false}} on:focus={() => {isFocused = true}}/>


<Settingsmodal bind:settingsOpen={isSettingsOpen} bind:hornOpen={isHornOpen}/>
<Connectionsmodal bind:connectionsOpen={isConnectionsOpen}/>
<Hornmodal bind:hornOpen={isHornOpen}/>

<body>

<div class="flex w-[98vw] h-[100vh] select-none">
    {#if ($joystick_mode === "joystick")}
    <Joystick/>
    {:else}
    <Dpad/>
    {/if}
    
    <Fourbuttonpad/>

    <Sidebuttons bind:settingsOpen={isSettingsOpen} bind:connectionsOpen={isConnectionsOpen}/>

</div>
    

</body>