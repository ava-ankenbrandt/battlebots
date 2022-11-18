<script lang='ts'>
    import { onMount } from 'svelte';

    let windowWidth: number;
    let windowHeight: number;

    onMount(async () => {
		if (windowWidth < windowHeight) {
            alert('Please use landscape mode!');
        }
	});
</script>

<svelte:window bind:innerWidth={windowWidth} bind:innerHeight={windowHeight}/>

<div class="flex w-screen h-screen">
    <div class="grid h-full aspect-square bg-base-100 place-items-center max-w-[600px] border-slate-900 border-2">content</div>

    
    <div class="flex-1 flex justify-center items-center align-middle">
        <!-- <div 
        class="aspect-square w-[min(100vh,calc((50vw-7.5rem)))] h-[min(100vh,calc((50vw-7.5rem)))]"> -->
        <div class="p-0 flex grow h-[100vh]">
            <div class="grid grid-cols-2 gap-4 p-2 w-full h-full">
                <div class="card bg-primary shadow-xl">
                    <div class="card-body items-center text-center text-primary-content">
                        A
                    </div>
                </div>
                <div class="card bg-primary shadow-xl">
                    <div class="card-body items-center text-center text-primary-content">
                        A
                    </div>
                </div>
                <div class="card bg-primary shadow-xl">
                    <div class="card-body items-center text-center text-primary-content">
                        A
                    </div>
                </div>
                <div class="card bg-primary shadow-xl">
                    <div class="card-body items-center text-center text-primary-content">
                        A
                    </div>
                </div>
            </div>
        </div>

        
    </div>
    

    <div class="flex-col h-20 w-20 card bg-base-300 rounded-box place-items-center">content3</div>
  </div>

