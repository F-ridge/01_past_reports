library(ggm)
options(digits=3)

col2par <- function(R){
    X = solve(R)
    d = sqrt(diag(X))
    P = -X / (d %*% t(d))
    diag(P) = 1
    P
}

select.ij <- function(P, amat){
    p <- nrow(P)
    minabsP <- Inf
    for(i in (2:p)){
        for(j in (1:(i - 1))){
            if(amat[i, j] == 1 && abs(P[i, j]) < minabsP){
                minabsP <- abs(P[i, j])
                i0 <- i
                j0 <- j
    }}}
    c(i0, j0)
}

covselection <- function(data){
    X <- data
    n <- nrow(X)
    p <- ncol(X)
    R <- cor(X)
    M <- R
    amat <- matrix(1, p, p) - diag(p)
    dimnames(amat) <- dimnames(R)
    P <- col2par(M)
    P_0 <- P
    prev_aic <- 0
    aic <- 0
    n_iter <- 0
    repeat{
        prev_amat <- amat
        rm_edge <- select.ij(P, amat)
        amat[rm_edge[1], rm_edge[2]] <- amat[rm_edge[2], rm_edge[1]] <- 0
        n_iter <- n_iter + 1
        f <- fitConGraph(amat, R, n)
        aic <- f$dev - 2 * f$df
        print(paste(
            'removed edge: (', rm_edge[1], ', ', rm_edge[2], '), ',
            'step: ', n_iter, ', ',
            'AIC: ', aic, sep=''))
        if(aic > prev_aic){
            print(paste('iterarion ended at step', n_iter))
            break
        }else{
            prev_aic <- aic
            M <- f$Shat
            P <- col2par(M)
        }}
    return(list(R, P_0, M, P, prev_amat))
    # R: 相関行列
    # P_0: 偏相関行列
    # M: 相関行列の推定値
    # P: 偏相関行列の推定値
    # prev_amat: グラフ
}