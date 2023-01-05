<script lang="ts">
    export let title: string;
    export let checked: boolean = false;
</script>

<div class="flex flex-row p-1 items-center grow w-full content-between">
    <h1 class="font-bold mr-auto">{title}</h1>
    <input type="checkbox" class="checkbox" bind:checked={checked}/>
</div>