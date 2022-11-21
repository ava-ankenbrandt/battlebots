<script lang='ts'>
    import { onMount } from 'svelte';

    let windowWidth: number;
    let windowHeight: number;

    function handleClick() { 
        alert('clicked!!!!');
    }

    function Xdown() {}
    function Xup() {}
    function Ydown() {}
    function Yup() {}
    function Adown() {}
    function Aup() {}
    function Bdown() {}
    function Bup() {}

    onMount(async () => {
		if (windowWidth < windowHeight) {
            alert('Please use landscape mode!');
        }
	});
</script>

<svelte:window bind:innerWidth={windowWidth} bind:innerHeight={windowHeight}/>

<div class="flex w-screen h-screen">
    <div class="relative h-full aspect-square bg-base-100 place-items-center max-w-[600px]">
        <svg class="absolute left-0 right-0 top-0 w-full fill-primary stroke-base-100 stroke-1" viewBox="0 0 50 50" id="canvas">
            <polygon points="0,0 50,0 25.0,25.0"></polygon>
            <polygon points="0,0 0,50 25.0,25.0"></polygon>
            <polygon points="50,50 50,0 25.0,25.0"></polygon>
            <polygon points="50,50 0,50 25.0,25.0"></polygon>
        </svg>
        <svg class="absolute left-0 right-0 top-0 w-full fill-primary-content stroke-none" viewBox="0 0 50 50" id="canvas2">
            <polygon points="10,20 10,30 6,25"></polygon>
            <polygon points="20,10 30,10 25,6"></polygon>
            <polygon points="40,20 40,30 44,25"></polygon>
            <polygon points="20,40 30,40 25,44"></polygon>
            <polygon on:click={handleClick} class="fill-transparent" points="0,0 50,0 25.0,25.0"></polygon>
            <polygon on:click={handleClick} class="fill-transparent" points="0,0 0,50 25.0,25.0"></polygon>
            <polygon on:click={handleClick} class="fill-transparent" points="50,50 50,0 25.0,25.0"></polygon>
            <polygon on:click={handleClick} class="fill-transparent" points="50,50 0,50 25.0,25.0"></polygon>

        </svg>
    </div>

    
    <div class="flex-1 flex justify-center items-center align-middle">
        
        <div class="p-0 flex grow h-[100vh]">
            <div class="grid grid-cols-2 gap-2 p-1 w-full h-full">
                <div class="flex justify-center items-center align-middle rounded-2xl bg-primary" on:mousedown={Xdown} on:mouseup={Xup}>
                    <p class="text-primary-content text-4xl font-bold">
                        X
                    </p>
                </div>
                <div class="flex justify-center items-center align-middle rounded-2xl bg-primary" on:mousedown={Ydown} on:mouseup={Yup}>
                    <p class="text-primary-content text-4xl font-bold">
                        Y
                    </p>
                </div>
                <div class="flex justify-center items-center align-middle rounded-2xl bg-primary" on:mousedown={Adown} on:mouseup={Aup}>
                    <p class="text-primary-content text-4xl font-bold">
                        A
                    </p>
                </div>
                <div class="flex justify-center items-center align-middle rounded-2xl bg-primary" on:mousedown={Bdown} on:mouseup={Bup}>
                    <p class="text-primary-content text-4xl font-bold">
                        B
                    </p>
                </div>
            </div>
        </div>

        
    </div>
    

    <div class="flex-col p-1 space-y-2">
        <div class="w-20 card rounded-box items-center align-middle justify-center bg-neutral pb-2.5">
            <p class="text-neutral-content text-7xl font-bold">
                ⚙
            </p>
        </div>
        <div class="w-20 card rounded-box items-center align-middle justify-center bg-neutral h-20">
            <p class="text-neutral-content text-4xl font-bold">
                ⏚
            </p>
        </div>
    </div>
  </div>

