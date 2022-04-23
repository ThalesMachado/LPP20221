#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rankTarefa;
    if(size % 2 != 0){
        printf("O número de processos deve ser par\n");
        MPI_Abort( MPI_COMM_WORLD, 1);
    } else {
        if(rank < (size / 2)) {
            rankTarefa = rank;
            printf("Tarefa %d enviou seu id para %d\n", rank, ((size / 2) + rank));
            MPI_Send(&rankTarefa, 1, MPI_INT, ((size / 2) + rank), 0, MPI_COMM_WORLD);
        } else {
            MPI_Recv(&rankTarefa, 1, MPI_INT, ((size / 2) - rank) , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            printf("Tarefa %d recebeu id da tarefa %d\n", rank, rankTarefa);
        }
    }
    
    printf("Rank: %d/%d\n", rank, size);
    
    MPI_Finalize();
    
    return 0;
}