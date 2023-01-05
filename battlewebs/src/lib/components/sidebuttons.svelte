<script lang="ts">
    export let settingsOpen: boolean
    export let connectionsOpen: boolean
</script>

<div class="flex-col p-1 space-y-2">
        <button class="w-20 card rounded-box items-center align-middle justify-center bg-neutral focus:bg-neutral-focus h-20 modal-button select-none" on:click={()=>settingsOpen = true}>
            <p class="text-neutral-content text-6xl font-bold">
                ⎈
            </p>
        </button>
        <button class="w-20 card rounded-box items-center align-middle justify-center bg-neutral focus:bg-neutral-focus h-20 modal-button select-none" on:click={()=>connectionsOpen = true}>
            <p class="text-neutral-content text-4xl font-bold">
                ⏚
            </p>
        </button>
    </div>
  