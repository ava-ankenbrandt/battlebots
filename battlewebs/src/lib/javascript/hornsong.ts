type Note = {freq: number, duration: number}
// 15 allowed frequencies (CDEFGABCDEFGABC) encoded to 1 through 15
// 0 means no sound for duration
// duration is stored to the millisecond. Horn songs can be up to 5sec long.

export class HornSong {
    private song : Array<Note> = []
    
    public eraseSong() {

    }

    addNote(freq: number) {

    }
}