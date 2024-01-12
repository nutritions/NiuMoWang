// func == 1
static void scan_vma(void)
{
    printk("func == 1, %s\n", __func__);
    struct mm_struct *mm = get_task_mm(my_task_info.task);
    if (mm)
    {
        // TODO:遍历VMA将VMA的个数记录到my_task_info的vma_cnt变量中
        int cnt = 0;
        struct vm_area_struct* p = mm->mmap;
        while (p){
            cnt++;
            p = p->vm_next;
        }
        my_task_info.vma_cnt = cnt;
        mmput(mm);
    }
}

// func == 2
static void print_mm_active_info(void)
{
    printk("func == 2, %s\n", __func__);
    // TODO: 1. 遍历VMA，并根据VMA的虚拟地址得到对应的struct page结构体（使用mfollow_page函数）
    // struct page *page = mfollow_page(vma, virt_addr, FOLL_GET);
    // unsigned int unused_page_mask;
    // struct page *page = mfollow_page_mask(vma, virt_addr, FOLL_GET, &unused_page_mask);
    // TODO: 2. 使用page_referenced活跃页面是否被访问，并将被访问的页面物理地址写到文件中
    // kernel v5.13.0-40及之后可尝试
    // unsigned long vm_flags;
    // int freq = mpage_referenced(page, 0, (struct mem_cgroup *)(page->memcg_data), &vm_flags);
    // kernel v5.9.0
    // unsigned long vm_flags;
    // int freq = mpage_referenced(page, 0, page->mem_cgroup, &vm_flags);
    struct mm_struct *mm = get_task_mm(my_task_info.task);
    if(mm) {
        struct vm_area_struct *vma = mm -> mmap;
        while (vma) {
            unsigned long vm_addr = vma->vm_start;
            int freq;
            for(vm_addr; vm_addr < vma->vm_end; vm_addr += page_add){
                struct page *page = mfollow_page(vma, vm_addr, FOLL_GET);
                if(!IS_ERR_OR_NULL(page)) {
                    unsigned long vm_flags;
                    freq = mpage_referenced(page, 0, (struct mem_cgroup *)(page->memcg_data), &vm_flags);
                    if(freq) {
                    record_one_data(page_to_pfn(page));
                    }
                } else {
                    continue;
                }
                
            }
            vma = vma -> vm_next;
        }
        flush_buf(1);
    }
}

// func = 3
static void traverse_page_table(struct task_struct *task)
{
    printk("func == 3, %s\n", __func__);
    struct mm_struct *mm = get_task_mm(my_task_info.task);
    if (mm)
    {
        // TODO:遍历VMA，并以PAGE_SIZE为粒度逐个遍历VMA中的虚拟地址，然后进行页表遍历
        // record_two_data(virt_addr, virt2phys(task->mm, virt_addr));
        struct vm_area_struct *vma = mm -> mmap;
        while (vma) {
            unsigned long vm_addr = vma->vm_start;
            int freq;
            for(vm_addr; vm_addr < vma->vm_end; vm_addr += page_add){
            	unsigned long page_phys = virt2phys(task->mm, vm_addr);
                record_two_data(vm_addr, page_phys);
            }
            vma = vma -> vm_next;
        }
        flush_buf(1);
        mmput(mm);
    }
    else
    {
        pr_err("func: %s mm_struct is NULL\n", __func__);
    }
}

// func == 4 或者 func == 5
static void print_seg_info(void)
{
    struct mm_struct *mm;
    unsigned long addr;
    printk("func == 4 or func == 5, %s\n", __func__);
    mm = get_task_mm(my_task_info.task);
    if (mm == NULL)
    {
        pr_err("mm_struct is NULL\n");
        return;
    }
    // TODO: 根据数据段或者代码段的起始地址和终止地址得到其中的页面，然后打印页面内容到文件中
    // 相关提示：可以使用follow_page函数得到虚拟地址对应的page，然后使用addr=kmap_atomic(page)得到可以直接
    //          访问的虚拟地址，然后就可以使用memcpy函数将数据段或代码段拷贝到全局变量buf中以写入到文件中
    //          注意：使用kmap_atomic(page)结束后还需要使用kunmap_atomic(addr)来进行释放操作
    //          正确结果：如果是运行实验提供的workload，这一部分数据段应该会打印出char *trace_data，
    //                   static char global_data[100]和char hamlet_scene1[8276]的内容。
    unsigned long start_data_addr = mm -> start_data;
    unsigned long end_data_addr = mm -> end_data;

    struct vm_area_struct *vma = mm -> mmap;

    while (vma) {
        unsigned long vm_addr = vma ->vm_start;
        for(vm_addr; vm_addr < vma -> vm_end; vm_addr += page_add){
            struct page *page = mfollow_page(vma, vm_addr, FOLL_GET);
            if(!IS_ERR_OR_NULL(page)) {
                char* addr = NULL;
                addr = kmap_atomic(page);
                kunmap_atomic(addr);
                if(vm_addr >= start_data_addr)//开头在地址之前
                {
                    if(vm_addr + page_add <= end_data_addr)//结尾在下一页地址之后
                    {
                        //输出当前页全部内容
                        memcpy(buf, addr, PAGE_SIZE);
                        curr_buf_length += PAGE_SIZE;
                        flush_buf(0);
                    }
                    else if(vm_addr <= end_data_addr)//结尾在下一页地址前且在当前页地址后
                    {
                        //输出当前页前面一部分（有数据段的部分）
                        memcpy(buf, addr, end_data_addr - vm_addr);
                        curr_buf_length += end_data_addr - vm_addr;
                        flush_buf(0);
                    }
                }
                else//开头在当前页地址后
                {
                    if(vm_addr + page_add >= end_data_addr)//结尾在下一页地址前
                    {
                        //输出当前页中间一部分（有数据段的部分）
                        memcpy(buf, addr + start_data_addr - vm_addr, end_data_addr - start_data_addr);
                        curr_buf_length += end_data_addr - start_data_addr;
                        flush_buf(0);
                    }
                    else if(vm_addr + page_add >= start_data_addr)//结尾在下一页地址后且开头在下一页地址前
                    {
                        //输出当前页后面一部分（有数据段的部分）
                        memcpy(buf, addr + start_data_addr - vm_addr, vm_addr + page_add - start_data_addr);
                        curr_buf_length += vm_addr + page_add - start_data_addr;
                        flush_buf(0);
                    }
                }
                
            }
        }
        vma = vma -> vm_next;
    }
    mmput(mm);
}

static unsigned long virt2phys(struct mm_struct *mm, unsigned long virt)
{
    struct page *page = NULL;
    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    /* TODO: 多级页表遍历：pgd->pud->pmd->pte，然后从pte到page，最后得到pfn，
     */   
    pgd = pgd_offset(mm, virt); 
    pud = pud_offset((p4d_t *)pgd, virt);
    pmd = pmd_offset(pud, virt);
    pte = pte_offset_kernel(pmd, virt); 
    page = pte_page(*pte);
    if (page)
    {
        // 调用 page_to_pfn 函数将页面结构体转换为页面的物理页框号（pfn），并返回该值
        return page_to_pfn(page);
    }
    else
    {
        pr_err("func: %s 页面为空\n", __func__);
        return 0; // 返回 0 而不是 NULL，适应 unsigned long 的返回类型
    }
}