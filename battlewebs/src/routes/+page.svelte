<script lang='ts'>
    import { onMount } from 'svelte';
    import Dpad from "$lib/components/dpad.svelte";
    import Settingsmodal from '$lib/components/settingsmodal.svelte';
	import Sidebuttons from '$lib/components/sidebuttons.svelte';
	import Fourbuttonpad from '$lib/components/fourbuttonpad.svelte';
	import Joystick from '$lib/components/joystick.svelte';

    let windowWidth: number;
    let windowHeight: number;

    function handleClick() { 
        alert('clicked!!!!');
    }

    function rotateAlert() {
        alert('Please use landscape mode!');
    }

    let isSettingsOpen = false

    onMount(() => {
		if (windowWidth < windowHeight) {
            rotateAlert();
        }
	});
</script>

<svelte:window bind:innerWidth={windowWidth} bind:innerHeight={windowHeight}/>


<Settingsmodal bind:settingsOpen={isSettingsOpen}></Settingsmodal>


<body>

<div class="flex w-[98vw] h-[100vh]">
    <Joystick></Joystick>
    <!-- <Dpad></Dpad> -->
    
    <Fourbuttonpad></Fourbuttonpad>

    <Sidebuttons bind:settingsOpen={isSettingsOpen}></Sidebuttons>

</div>
    

</body>