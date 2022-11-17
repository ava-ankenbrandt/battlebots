<script lang='ts'>
    import { onMount } from 'svelte';

    let windowWidth: number;
    let windowHeight: number;

    onMount(async () => {
		if ((windowWidth > 600) || (true)) {

        }
	});
</script>

<svelte:window bind:innerWidth={windowWidth} bind:innerHeight={windowHeight}/>

<h1 class="w-full text-center">Welcome to SvelteKit</h1>
<p>Visit <a href="https://kit.svelte.dev">kit.svelte.dev</a> to read the documentation</p>
<div class="flex w-full">
    <div class="grid h-20 flex-grow card bg-base-300 rounded-box place-items-center">content</div>
    <div class="divider divider-horizontal"></div>
    <div class="grid h-20 flex-grow card bg-base-300 rounded-box place-items-center">content</div>
    <div class="divider divider-horizontal"></div>
    <div class="grid h-20 flex-grow card bg-base-300 rounded-box place-items-center">content</div>
  </div>

