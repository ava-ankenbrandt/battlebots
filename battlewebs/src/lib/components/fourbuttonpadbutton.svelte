<script lang="ts">
    export let title : string;
    export let active : boolean;
    
</script>

<button class="flex justify-center items-center align-middle rounded-2xl bg-primary select-none active:bg-primary-focus" class:bg-primary-focus={active === true} on:pointerdown on:pointerleave on:pointerup>
    <p class="text-primary-content text-4xl font-bold">
        {title}
    </p>
</button>