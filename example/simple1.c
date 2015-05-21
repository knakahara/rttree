#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <stdint.h>
#include <stddef.h>

#include <rttree.h>

#define SIMPLE1_DEBUG 1
#ifdef SIMPLE1_DEBUG
#define DPRINTF(msg) printf msg
#else
#define DPRINTF(msg)
#endif

struct simple_node {
	rtnode_t node;
	uint32_t key;
	char value[32];
};

static rtt_inode_t * simple_ialloc(rttree_t *);
static void simple_ifree(rttree_t *, rtt_inode_t *);
static void simple_iunref(rttree_t *, rtt_inode_t *);
static rtt_ptr_t *simple_lalloc(rttree_t *, rtt_size_t);
static void simple_lfree(rttree_t *, rtt_size_t, rtt_ptr_t *);
static void simple_lunref(rttree_t *, rtt_size_t, rtt_ptr_t *);

rtt_alloc_t simple_alloc = {
	.rtta_inode_alloc = simple_ialloc,
	.rtta_inode_free = simple_ifree,
	.rtta_inode_unref = simple_iunref,
	.rtta_lut_alloc = simple_lalloc,
	.rtta_lut_free = simple_lfree,
	.rtta_lut_unref = simple_lunref,
};

static rtt_inode_t *
simple_ialloc(rttree_t *root)
{
	rtt_inode_t *inode;

	if (root == NULL) {
		DPRINTF(("%s: root is NULL\n", __func__));
		return NULL;
	}

	inode = malloc(sizeof(*inode));
	if (inode == NULL)
		DPRINTF(("%s: malloc(sizeof(*inode) failed\n", __func__));

	return inode;
}

static void
simple_ifree(rttree_t *root, rtt_inode_t *inode)
{
	if (root == NULL) {
		DPRINTF(("%s: root is NULL\n", __func__));
		return;
	}
	if (inode == NULL) {
		DPRINTF(("%s: inode is NULL\n", __func__));
		return;
	}

	free(inode);

	return;
}

static void
simple_iunref(rttree_t *root, rtt_inode_t *inode)
{
	if (root == NULL) {
		DPRINTF(("%s: root is NULL\n", __func__));
		return;
	}
	if (inode == NULL) {
		DPRINTF(("%s: inode is NULL\n", __func__));
		return;
	}

	/* XXXX */

	return;
}

static rtt_ptr_t *
simple_lalloc(rttree_t *root, rtt_size_t lut_size)
{
	rtt_ptr_t *lut;

	if (root == NULL) {
		DPRINTF(("%s: root is NULL\n", __func__));
		return NULL;
	}
	if (lut_size == 0) {
		DPRINTF(("%s: lut_size is 0\n", __func__));
		return NULL;
	}
	lut = malloc(sizeof(*lut) * lut_size);
	if (lut == NULL) {
		DPRINTF(("%s: inode is NULL\n", __func__));
	}

	return NULL;
}

static void
simple_lfree(rttree_t *root, rtt_size_t lut_size, rtt_ptr_t *lut)
{
	if (root == NULL) {
		DPRINTF(("%s: root is NULL\n", __func__));
		return;
	}
	if (lut_size == 0) {
		DPRINTF(("%s: lut_size is 0\n", __func__));
		return;
	}
	if (lut == NULL) {
		DPRINTF(("%s: lut is NULL\n", __func__));
		return;
	}

	/*XXXX Is current size check required? */

	free(lut);

	return;
}

static void
simple_lunref(rttree_t *root, rtt_size_t lut_size, rtt_ptr_t *lut)
{
	if (root == NULL) {
		DPRINTF(("%s: root is NULL\n", __func__));
		return;
	}
	if (lut_size == 0) {
		DPRINTF(("%s: lut_size is 0\n", __func__));
		return;
	}
	if (lut == NULL) {
		DPRINTF(("%s: lut is NULL\n", __func__));
		return;
	}

	/* XXXX */

	return;
}

/*****************************************************************************/

int
main(void)
{
	int ret;
	rttree_t *root;

	root = malloc(sizeof(*root));
	if (root == NULL)
		perror("malloc(root)");

	ret = rttree_init(root,
	    RTTREE_PTR_NONE,
	    offsetof(struct simple_node, key),
	    RTT_LUT_2,
	    RTTREE_CMASK_NONE, /* don;t care "color" */
	    &simple_alloc,
	    NULL,
	    NULL); /* don't care statistics */
	if (ret != RTTREE_OK) {
		printf("error rttree_init(): ret=%d\n", ret);
		exit(1);
	}

	exit(0);
}
