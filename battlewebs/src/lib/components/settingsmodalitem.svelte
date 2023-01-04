<script lang="ts">
    export let title : string;
    export let options: string[];
    export let selected: string = options[0];
</script>

<div class="flex flex-row p-1 items-center grow w-full content-between">
    <h1 class="font-bold">{title}</h1>
    <div class="btn-group ml-auto">
        {#each options as option}
            <button
            class="btn"
            class:btn-active={option === selected}
            on:click={() => selected = option}
            >
            {option}
            </button>
        {/each}
    </div>
</div>