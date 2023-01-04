<script lang="ts">
    export let title : string
</script>

<button class="flex justify-center items-center align-middle rounded-2xl bg-primary active:bg-primary-focus select-none" on:pointerdown on:pointerleave on:pointerup>
    <p class="text-primary-content text-4xl font-bold">
        {title}
    </p>
</button>